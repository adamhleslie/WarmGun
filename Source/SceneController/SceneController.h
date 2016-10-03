#pragma once

#include "Module.h"

#include <list>
#include <OgreSceneManager.h>

#include "Scene.h"

class Renderer;

class SceneController : public Module
{
public:

// PUBLIC API
	SceneController(Renderer* renderer, Ogre::SceneType sceneType);
	~SceneController() {}

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
