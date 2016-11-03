#include "SceneController.h"

#include <string>
#include <iostream>
#include <cassert>
#include <OgreSceneManager.h>

#include "Renderer.h"
#include "Scene.h"
#include "Core.h"

SceneController::SceneController (Renderer* renderer)
:	mRenderer(renderer)
{
	assert(mRenderer);
	stopUpdating();
	initScenes();
}

void SceneController::addScene (Scene& scene)
{
	mSceneList.push_back(scene);
}

void SceneController::loadNextScene (bool additive /* = false */)
{
	assert(isLoaded());

	mCurScene++;
	assert(mCurScene != mSceneList.end());

	Core* core = getCore();
	if (!additive)
	{
		mRenderer->destroyCamera();
		mRenderer->getSceneManager()->clearScene();
		core->destroyAllEntities();
	}

	(*(mCurScene->loadScene))(core);
}

void SceneController::postLoad ()
{
	// loadInitialScene();
}

std::string SceneController::getIP ()
{
	string retVal;
	std::cout << "INPUT IP ADDRESS: " << std::endl;
	std::cin >> retVal;
	return retVal;
}

void SceneController::loadInitialScene ()
{
	assert(isLoaded());
	assert(!mSceneList.empty());

	mCurScene = mSceneList.begin();
	(*(mCurScene->loadScene))(getCore());
}