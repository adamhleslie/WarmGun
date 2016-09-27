#pragma once

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

	virtual void update() = 0;
	
	virtual void loadScene() = 0;

private:
	void setup() override;

protected:
	Renderer* mRenderer = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;
	Ogre::SceneType mSceneType;
};
