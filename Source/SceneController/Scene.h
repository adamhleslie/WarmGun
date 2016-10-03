#pragma once

#include <OgreSceneManager.h>

class Core;
class Renderer;

struct Scene
{
	typedef void (*LoadSceneFunc)(Core* core);
	LoadSceneFunc loadScene = nullptr;

	Scene (LoadSceneFunc loadSceneFunc) : loadScene(loadSceneFunc) {}
	~Scene () {}
};

