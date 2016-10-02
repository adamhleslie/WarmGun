#pragma once

#include <string>
#include <list>

#include "Module.h"
#include "Scene.h"

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

class Renderer;

class SceneController : public Module
{
public:

// PUBLIC API
	SceneController(Renderer* renderer, Ogre::SceneType sceneType);
	~SceneController() {}

	void update() override;

	// Modifiers //
	void addScene(Scene& scene);
	void loadNextScene(bool additive = false);

// RESTRICTED API
protected:
	void onLoadCallback(Core* core) override;

private:
	Renderer* mRenderer = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;

	std::list<Scene> mSceneList;
	std::list<Scene>::iterator mCurScene;

	// Loads the first scene in the scene list
	void loadInitialScene(Core* core);

	// Adds the initial scenes to the scene list
	// Implemented in Scenes.cpp
	void initScenes();
};
