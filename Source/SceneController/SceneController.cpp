#include "SceneController.h"

#include <cassert>

#include "Core.h"
#include "Renderer.h"
#include "Scene.h"

SceneController::SceneController (Renderer* renderer, Ogre::SceneType sceneType)
:	mRenderer(renderer)
{
	assert(renderer);
	mSceneMgr = mRenderer->mRoot->createSceneManager(sceneType);
}

void SceneController::update ()
{
	(*(mCurScene->updateScene))();
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
		core->destroyAllEntities();

	(*(mCurScene->loadScene))(core, mSceneMgr, mRenderer);
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
	(*(mCurScene->loadScene))(core, mSceneMgr, mRenderer);
}