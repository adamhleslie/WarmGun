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

using Ogre::Vector3;
using Ogre::Quaternion;

namespace scene1
{
	Ogre::SceneManager* mSceneMgr = nullptr;

	void constructWall(Core* core, const Vector3& position, const Quaternion& rotation)
	{
		Entity* ground = core->createEntity(kCube, "Rockwall", false, Vector3(1, 0, 1), position, rotation);
		ground->getTransform()->attachRigidbody(kCube, Vector3(25, 0, 25));
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
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDirection(-.1, -1, 0);
		spotLight->setPosition(Vector3(100, 600, 0));

		// Set up camera
		Ogre::Camera* mainCam = mSceneMgr->createCamera("Main Camera");
		mainCam->setPosition(0, 400, 0);
		mainCam->lookAt(Vector3(0, 1, .1));
		mainCam->setNearClipDistance(5);
		renderer->switchCamera(mainCam);

		// Set up Sphere
		constexpr float kScale = .1;
		Entity* sphere = core->createEntity(kSphere, "BumpyMetal", true, Vector3(kScale, kScale, kScale), Vector3(0, 300, 0));
		sphere->getTransform()->attachRigidbody(kSphere, Vector3(kScale * 50, 0, 0), 1, .1);

		Ogre::ParticleSystem* mParticle = mSceneMgr->createParticleSystem("Sun", "Examples/Fireworks");
		sphere->getTransform()->getSceneNode()->attachObject(mParticle);
		mParticle->setEmitting(true);

		// Set up paddle
		Entity* paddle = core->createEntity(kCube, "BumpyMetal", true, Vector3(kScale, .0001, kScale), Vector3(0, 20, 0));
		paddle->getTransform()->attachRigidbody(kCube, Vector3(kScale * 50, kScale * 50, kScale * 50), 0, .1);

		// Set up ground
		Entity* ground = core->createEntity(kCube, "Rockwall", false, Vector3(1, 0, 1));
		ground->getTransform()->attachRigidbody(kCube, Vector3(25, 0, 25));
		constructWall(core, Vector3::ZERO, Quaternion::IDENTITY);

		// Set up walls
		constructWall(core, Vector3(-50, 50, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(-50, 150, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(-50, 250, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));

		constructWall(core, Vector3(50, 50, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(50, 150, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));
		constructWall(core, Vector3(50, 250, 0), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));

		constructWall(core, Vector3(0, 50, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 150, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 250, -50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));

		constructWall(core, Vector3(0, 50, 50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 150, 50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
		constructWall(core, Vector3(0, 250, 50), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));
	}
}

void SceneController::initScenes ()
{
	Scene scene1(scene1::load);
	addScene(scene1);
}