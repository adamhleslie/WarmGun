#pragma once

#include "Module.h"

#include <list>
#include "Scene.h"

class Renderer;

class SceneController : public Module
{
public:
	SceneController(Renderer* renderer);
	~SceneController() {}

	// Add a scene to the end of the scene list
	void addScene(Scene& scene);

	// Load the next scene in the scene list
	// if additive, prior scenes are not unloaded
	void loadNextScene(bool additive = false);

	void initSingleplayer();
	void initServer();
	void initClient();

protected:
	void postLoad() override;

private:
	Renderer* mRenderer = nullptr;

	std::list<Scene> mSceneList;
	std::list<Scene>::iterator mCurScene;

	// Loads the first scene in the scene list
	void loadInitialScene();

	// Adds the initial scenes to the scene list
	// Implemented in Scenes.cpp
	void initScenes();
};
