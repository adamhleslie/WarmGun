#include "SceneController.h"

#include <cstdlib>
#include <string>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreMeshManager.h>
#include <OgreMath.h>
#include <OgrePlane.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <OgreParticleSystem.h>

#include "Core.h"
#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "BoundMovement.h"
#include "WatchThis.h"
#include "Transform.h"
#include "AudioPlayer.h"
#include "Physics.h"
#include "PaddleController.h"

using Ogre::Vector3;
using Ogre::Quaternion;

namespace scene1
{
	Ogre::SceneManager* mSceneMgr = nullptr;

	void constructWall(Core* core, const Vector3& position, const Quaternion& rotation)
	{
		Entity* ground = core->createEntity(kCube, "BumpyMetal", false, Vector3(1, 0, 1), position, rotation);
		ground->getTransform()->attachRigidbody(kCube, Vector3(25, 1, 25), 0, 1.5);
	}

	void load (Core* core)
	{
		Renderer* renderer = core->getRenderer();
		Physics* physics = core->getPhysics();
		mSceneMgr = renderer->getSceneManager();

		// Set up scene lighting
		mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .3));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
		spotLight->setDiffuseColour(1, 0, 0);
		spotLight->setSpecularColour(1, 0, 0);
		spotLight->setType(Ogre::Light::LT_POINT);
		spotLight->setDirection(0, 0, 0);
		spotLight->setPosition(Vector3(0, 250, 0));

		Ogre::Light* spotLight2 = mSceneMgr->createLight("SpotLight2");
		spotLight2->setDiffuseColour(0, 0, .5);
		spotLight2->setSpecularColour(0, 0, .5);
		spotLight2->setType(Ogre::Light::LT_POINT);
		spotLight2->setDirection(0, 0, 0);
		spotLight2->setPosition(Vector3(0, 300, 0));

		// Set up camera
		Ogre::Camera* mainCam = mSceneMgr->createCamera("Main Camera");
		mainCam->setPosition(0, 400, 0);
		mainCam->lookAt(Vector3(0, 1, .1));
		mainCam->setNearClipDistance(5);
		renderer->switchCamera(mainCam);

		// Set up Sphere
		constexpr float kScale = .1;
		Entity* sphere = core->createEntity(kSphere, "Chrome", true, Vector3(kScale, kScale, kScale), Vector3(0, 300, 0));
		sphere->getTransform()->attachRigidbody(kSphere, Vector3(kScale * 50, 0, 0), 10, 1, true);
		sphere->isBall = true;
		AudioPlayer* ap = sphere->createComponent<AudioPlayer>();

		Ogre::ParticleSystem* mParticle = mSceneMgr->createParticleSystem("Sun", "Examples/Fireworks");
		sphere->getTransform()->getSceneNode()->attachObject(mParticle);
		mParticle->setEmitting(false);

		// Set up paddle
		Entity* paddle = core->createEntity(kCube, "Rockwall", true, Vector3(kScale, kScale, kScale), Vector3(0, 20, 0));
		paddle->getTransform()->attachRigidbody(kCube, Vector3(kScale * 50, kScale * 50, kScale * 50), 0, 1);
		paddle->isPaddle = true;
		PaddleController* pt = paddle->createComponent<PaddleController>();
		pt->mCamera = mainCam;
		pt->ap = ap;


		// Set up ground
		Entity* ground = core->createEntity(kCube, "SpaceSkyPlane", false, Vector3(1, .01, 1), Vector3::ZERO, Quaternion(Ogre::Degree(180), Vector3(1, 0, 0)));
		ground->getTransform()->attachRigidbody(kCube, Vector3(25, 1, 25), 0, 0);
		ground->isGround = true;

		// Set up walls
		constructWall(core, Vector3(-50, 50, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(-50, 150, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(-50, 250, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));

		constructWall(core, Vector3(50, 50, 0), Quaternion(Ogre::Degree(-90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(50, 150, 0), Quaternion(Ogre::Degree(-90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(50, 250, 0), Quaternion(Ogre::Degree(-90), Vector3(1, 0, 0)));

		constructWall(core, Vector3(0, 50, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 150, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 250, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));

		constructWall(core, Vector3(0, 50, 50), Quaternion(Ogre::Degree(-90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 150, 50), Quaternion(Ogre::Degree(-90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 250, 50), Quaternion(Ogre::Degree(-90), Vector3(0, 0, 1)));
	}
}

void SceneController::initScenes ()
{
	Scene scene1(scene1::load);
	addScene(scene1);
}