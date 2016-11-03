#include "Physics.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Entity.h"
#include "AudioPlayer.h"
#include <OgreParticleSystem.h>
#include "GUI.h"
#include "NetManager.h"

// Temporary Begin
extern ContactProcessedCallback gContactProcessedCallback;

static bool sHitGround = false;
static GUI* sGui = nullptr;
static NetManager* sNetMgr = nullptr;
static btDiscreteDynamicsWorld* sDiscrete = nullptr;
static bool serverBall = true;

static bool HandleBallContact (btManifoldPoint& point, btCollisionObject* body0, btCollisionObject* body1)
{
	if (!sHitGround)
	{
		Entity* entity0 = static_cast<Entity*>(body0->getUserPointer());
		assert(entity0);

		Entity* entity1 = static_cast<Entity*>(body1->getUserPointer());
		assert(entity1);

		Entity* ball = nullptr;
		Entity* notBall = nullptr;
		
		if (entity0->isBall)
		{
			ball = entity0;
			notBall = entity1;
		}
		else if (entity1->isBall)
		{
			ball = entity1;
			notBall = entity0;
		}
		assert(ball);
		AudioPlayer* ballAudio = ball->getComponent<AudioPlayer>();
		assert(ballAudio);


		if (notBall->isServerPaddle)
		{
			ballAudio->playSound(1);
			btVector3 tmp(0, 10, 0);
			sDiscrete->setGravity(tmp);
			serverBall = false;
		}
		else if (notBall->isClientPaddle)
		{
			ballAudio->playSound(1);
			btVector3 tmp(0, 10, 0);
			sDiscrete->setGravity(tmp);
			serverBall = true;
		}
		else if (notBall->isPaddle)
		{
			// Play sound 1
			ballAudio->playSound(1);
			sGui->scorePoint();
			btVector3 tmp(0, 10, 0);
			sDiscrete->setGravity(tmp);
		}
		else if (notBall->isGround)
		{
			// Play sound 2
			// Enable emission
			Ogre::ParticleSystem* particle = dynamic_cast<Ogre::ParticleSystem*>(ball->getTransform()->getSceneNode()->getAttachedObject(1));
			assert(particle);
			particle->setEmitting(true);
			ballAudio->playSound(2);
			if (serverBall)
			{
				sNetMgr->setStatusChange(kClientWon);
				sGui->serverLose();
			}
			else
			{
				sNetMgr->setStatusChange(kServerWon);
				sGui->clientLose();
			}
			sHitGround = true;
		}
		else if (notBall->isCeiling)
		{
			// Play sound 1
			ballAudio->playSound(3);
			btVector3 tmp(0, -10, 0);
			sDiscrete->setGravity(tmp);
		}
		else
		{
			// Play sound 3
			ballAudio->playSound(3);
		}
	}

	return true;
}
// Temporary End

Physics::Physics (GUI* gui, NetManager* netMgr)
{
	stopUpdating();

	mCollisionConfig = new btDefaultCollisionConfiguration();
	mCollisionDispatcher = new btCollisionDispatcher(mCollisionConfig);
	mOverlappingPairs = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, mOverlappingPairs, mSolver, mCollisionConfig);
	sDiscrete = mWorld;
	btVector3 tmp(0, -10, 0);
	mWorld->setGravity(tmp);

	gContactProcessedCallback = (ContactProcessedCallback) HandleBallContact;

	assert(gui);
	sGui = gui;

	assert(netMgr);
	sNetMgr = netMgr;
}

Physics::~Physics ()
{
	delete mWorld;
	delete mSolver;
	delete mOverlappingPairs;
	delete mCollisionDispatcher;
	delete mCollisionConfig;
}

btDiscreteDynamicsWorld* Physics::getWorld ()
{
	assert(mWorld);
	return mWorld;
}