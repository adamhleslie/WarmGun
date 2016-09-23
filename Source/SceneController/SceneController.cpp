#include "SceneController.h"
#include "Renderer.h"

using namespace Ogre;

SceneController::SceneController (Renderer* renderer, Ogre::SceneType sceneType)
:	mRenderer(renderer)
{
	assert(renderer && renderer->mInitialized);
	mSceneMgr = renderer->mRoot->createSceneManager(sceneType);
}

SceneController::~SceneController ()
{
}

void SceneController::init ()
{
	loadScene();
	mInitialized = true;
}