#pragma once

#include <string>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderTargetListener.h>
#include <OgreMeshManager.h>

#include "Module.h"

class Renderer;

class SceneController : public Module
{
public:
	SceneController(Renderer* renderer, Ogre::SceneType sceneType);
	virtual ~SceneController();

	void update() override;

	void loadScene();

protected:
	Renderer* mRenderer = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;

private:
	Ogre::SceneNode* constructWall(const Ogre::Vector3& dir, const Ogre::Vector3& up, 
								   const Ogre::Vector3& pos, const std::string& name);

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::SceneNode* mBallNode = nullptr;

	Ogre::Camera* mCamera = nullptr;

	Ogre::Vector3 mWallDistances;
};
