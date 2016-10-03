#include "SceneController.h"

#include <cassert>

#include "Renderer.h"
#include "Scene.h"
#include "Core.h"

SceneController::SceneController (Renderer* renderer)
{
	assert(renderer);
	mSceneManager = renderer->getSceneManager();
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
		core->destroyAllEntities();
		mSceneManager->clearScene();
	}

	(*(mCurScene->loadScene))(core, mSceneManager);
}

void SceneController::onLoadCallback (Core* core)
{
	initScenes();
	loadInitialScene(core);
}

void SceneController::loadInitialScene (Core* core)
{
	assert(!mSceneList.empty());

	mCurScene = mSceneList.begin();
	(*(mCurScene->loadScene))(core, mSceneManager);
}