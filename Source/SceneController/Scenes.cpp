#include "SceneController.h"

#include <cstdlib>
#include <string>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreMeshManager.h>
#include <OgreMath.h>

#include "Core.h"
#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "BoundMovement.h"
#include "AudioPlayer.h"

using Ogre::Vector3;

namespace scene1
{
	Ogre::SceneManager* mSceneMgr = nullptr;

	Ogre::SceneNode* constructWall(const Vector3& norm, const Vector3& up, 
								   const Vector3& pos, const std::string& name)
	{
		Ogre::Plane p(norm, 0);
		Ogre::MeshManager::getSingleton().createPlane(
			name,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p, 
			800, 800, 20, 20, 
			true, 
			1, 1, 1, 
			up);
		Ogre::Entity* groundEntity = mSceneMgr->createEntity(name);
		Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
		node->attachObject(groundEntity);
		groundEntity->setCastShadows(false);
		groundEntity->setMaterialName("Examples/Rockwall");

		return node;
	}

	void load (Core* core)
	{
		Renderer* renderer = core->getRenderer();
		assert(renderer);

		mSceneMgr = renderer->getSceneManager();

		// Set up scene lighting
		mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .3));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
		spotLight->setDiffuseColour(1, 0, 0);
		spotLight->setSpecularColour(1, 0, 0);
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDirection(-.5, -1, 0);
		spotLight->setPosition(Vector3(400, 600, 0));

		// Set up camera
		Ogre::Camera* mCamera = mSceneMgr->createCamera("Main Camera");
		mCamera->setPosition(0, 0, 0);
		mCamera->lookAt(Vector3(200, 0, 0));
		mCamera->setNearClipDistance(5);
		renderer->switchCamera(mCamera);

		// Set up Sphere
		Entity* sphere = core->createEntity();
		sphere->createComponent<AudioPlayer>();

		BoundMovement* boundMove = sphere->createComponent<BoundMovement>();
		boundMove->mCamera = mCamera;
		boundMove->mBallRadius = 50;
		
		Ogre::Entity* sphereEntity = mSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
		sphereEntity->setCastShadows(true);
		sphereEntity->setMaterialName("Examples/BumpyMetal");
		boundMove->mBallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3 (0,150,0));
		boundMove->mBallNode->attachObject(sphereEntity);
		
		srand(time(NULL));
		boundMove->mBallVelocity = Vector3(Ogre::Math::RangeRandom(-1, 1),
										   Ogre::Math::RangeRandom(-1, 1),
										   Ogre::Math::RangeRandom(-1, 1));

		// // Set up walls
		constructWall(Vector3::UNIT_Y, Vector3::UNIT_Z, Vector3(0, -400, 0), "ground");
		constructWall(Vector3::NEGATIVE_UNIT_Y, Vector3::UNIT_Z, Vector3(0, 400, 0), "ceiling");
		constructWall(Vector3::UNIT_X, Vector3::UNIT_Z, Vector3(-400, 0, 0), "wall1");
		constructWall(Vector3::NEGATIVE_UNIT_X, Vector3::UNIT_Z, Vector3(400, 0, 0), "wall2");
		constructWall(Vector3::UNIT_Z, Vector3::UNIT_X, Vector3(0, 0, -400), "wall3");
		constructWall(Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_X, Vector3(0, 0, 400), "wall4");
		boundMove->mWallDistances = Vector3(400, 400, 400);
	}
}

void SceneController::initScenes ()
{
	Scene scene1(scene1::load);
	addScene(scene1);
}