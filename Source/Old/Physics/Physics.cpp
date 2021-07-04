#include "Physics.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Entity.h"
#include "Transform.h"
#include <OgreParticleSystem.h>

// Temporary Begin
extern ContactProcessedCallback gContactProcessedCallback;

static bool sHitGround = false;
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

		if (notBall->isPaddle)
		{
		}
		else if (notBall->isGround)
		{
			// Enable emission
			Ogre::ParticleSystem* particle = dynamic_cast<Ogre::ParticleSystem*>(ball->getTransform()->getSceneNode()->getAttachedObject(1));
			assert(particle);
			particle->setEmitting(true);
			sHitGround = true;
		}
		else
		{
		}
	}

	return true;
}
// Temporary End

Physics::Physics ()
{
	stopUpdating();

	mCollisionConfig = new btDefaultCollisionConfiguration();
	mCollisionDispatcher = new btCollisionDispatcher(mCollisionConfig);
	mOverlappingPairs = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, mOverlappingPairs, mSolver, mCollisionConfig);

	gContactProcessedCallback = (ContactProcessedCallback) HandleBallContact;
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