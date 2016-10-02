#include "Scene.h"
#include "SceneController.h"

#include "OgreMath.h"
#include <cstdlib>

#include "Renderer.h"

using namespace Ogre;

namespace scene1
{
	Ogre::SceneManager* mSceneMgr = nullptr;
	Renderer* mRenderer = nullptr;	

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::SceneNode* mBallNode = nullptr;
	Ogre::Camera* mCamera = nullptr;
	Ogre::Vector3 mWallDistances;

	Ogre::SceneNode* constructWall(const Ogre::Vector3& norm, const Ogre::Vector3& up, 
								   const Ogre::Vector3& pos, const std::string& name)
	{
		Plane p(norm, 0);
		MeshManager::getSingleton().createPlane(
			name,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p, 
			800, 800, 20, 20, 
			true, 
			1, 1, 1, 
			up);
		Entity* groundEntity = mSceneMgr->createEntity(name);
		SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
		node->attachObject(groundEntity);
		groundEntity->setCastShadows(false);
		groundEntity->setMaterialName("Examples/Rockwall");

		return node;
	}

	void load (Core* core, SceneManager* sceneMgr, Renderer* renderer)
	{
		mSceneMgr = sceneMgr;
		mRenderer = renderer;

		// Set up scene lighting
		mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .3));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		Light* spotLight = mSceneMgr->createLight("SpotLight");
		spotLight->setDiffuseColour(1, 0, 0);
		spotLight->setSpecularColour(1, 0, 0);
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDirection(-.5, -1, 0);
		spotLight->setPosition(Ogre::Vector3(400, 600, 0));

		// Set up camera
		mCamera = mSceneMgr->createCamera("Main Camera");
		mCamera->setPosition(0, 0, 0);
		mCamera->lookAt(Vector3(200, 0, 0));
		mCamera->setNearClipDistance(5);
		mRenderer->switchViewport(mCamera);

		// Set up Sphere
		mBallRadius = 50;
		Entity* sphereEntity = mSceneMgr->createEntity("mySphere", SceneManager::PT_SPHERE);
		sphereEntity->setCastShadows(true);
		sphereEntity->setMaterialName("Examples/BumpyMetal");
		mBallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3 (0,150,0));
		mBallNode->attachObject(sphereEntity);
		
		srand(time(NULL));
		mBallVelocity = Vector3(Math::RangeRandom(-1, -.3),
								Math::RangeRandom(-1, -.3),
								Math::RangeRandom(-1, -.3));

		// Set up walls
		SceneNode* tmp;
		constructWall(Vector3::UNIT_Y, Vector3::UNIT_Z, Vector3(0, -400, 0), "ground");
		constructWall(Vector3::NEGATIVE_UNIT_Y, Vector3::UNIT_Z, Vector3(0, 400, 0), "ceiling");
		constructWall(Vector3::UNIT_X, Vector3::UNIT_Z, Vector3(-400, 0, 0), "wall1");
		constructWall(Vector3::NEGATIVE_UNIT_X, Vector3::UNIT_Z, Vector3(400, 0, 0), "wall2");
		constructWall(Vector3::UNIT_Z, Vector3::UNIT_X, Vector3(0, 0, -400), "wall3");
		constructWall(Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_X, Vector3(0, 0, 400), "wall4");
		mWallDistances = Vector3(400, 400, 400);
	}

	void update ()
	{
		Vector3 initial = mBallNode->getPosition();
		mCamera->lookAt(initial);

		Vector3 next = initial + mBallVelocity;

		if (mBallVelocity.x >= 0 && (next.x + mBallRadius > mWallDistances.x) ||
			mBallVelocity.x <= 0 && (next.x - mBallRadius < -mWallDistances.x))
				mBallVelocity.x = -mBallVelocity.x;

		if (mBallVelocity.y >= 0 && (next.y + mBallRadius > mWallDistances.y) ||
			mBallVelocity.y <= 0 && (next.y - mBallRadius < -mWallDistances.y))
				mBallVelocity.y = -mBallVelocity.y;

		if (mBallVelocity.z >= 0 && (next.z + mBallRadius > mWallDistances.z) ||
			mBallVelocity.z <= 0 && (next.z - mBallRadius < -mWallDistances.z))
				mBallVelocity.z = -mBallVelocity.z;

		mBallNode->translate(mBallVelocity);
	}
}

void SceneController::initScenes ()
{
	Scene scene1(scene1::load, scene1::update);
	addScene(scene1);
}