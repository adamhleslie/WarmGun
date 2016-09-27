#include "SceneController.h"
#include "Renderer.h"

using namespace Ogre;

SceneController::SceneController (Renderer* renderer, Ogre::SceneType sceneType)
:	mRenderer(renderer),
	mSceneType(sceneType)
{
	assert(renderer);
}

SceneController::~SceneController ()
{
}

void SceneController::setup ()
{
	assert(mRenderer->isInitialized());
	mSceneMgr = mRenderer->mRoot->createSceneManager(mSceneType);
	loadScene();
}