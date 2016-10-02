#pragma once

#include <OgreSceneManager.h>

class Core;
class Renderer;

struct Scene
{
	typedef void (*LoadSceneFunc)(Core* core, Ogre::SceneManager* sceneMgr, Renderer* renderer);
	LoadSceneFunc loadScene = nullptr; 

	typedef void (*SceneUpdateFunc)();
	SceneUpdateFunc updateScene = nullptr;

	Scene (LoadSceneFunc loadSceneFunc, SceneUpdateFunc sceneUpdateFunc) 
		: loadScene(loadSceneFunc), updateScene(sceneUpdateFunc)  {}
	~Scene () {}
};

