#include "Renderer.h"

#include "CoreConfig.h"

using namespace Ogre;

void selectRenderSystem(Root* root);

Renderer::Renderer (Ogre::SceneType sceneType)
{
	// Renderer does not need to update every tick
	stopUpdating();
	
	mRoot = new Root("");
	// Load Plugins
#if _DEBUG
	mRoot->loadPlugin("RenderSystem_GL_d");
	mRoot->loadPlugin("Plugin_ParticleFX");
#else
	mRoot->loadPlugin("RenderSystem_GL");
	mRoot->loadPlugin("Plugin_ParticleFX");
#endif

	// Initialize with render system
	selectRenderSystem(mRoot);
	//TODO: change back to false to stop autocreating window
	mRoot->initialise(false);

	// Create scene manager, and render window
	mSceneManager = mRoot->createSceneManager(sceneType);
	//mWindow = mRoot->getAutoCreatedWindow();
	mWindow = mRoot->createRenderWindow(PROJECT_NAME, 640, 480, false);

	// Load in renderer resources
	ResourceGroupManager::getSingleton().addResourceLocation("./Media/Renderer", "FileSystem", "General");
	ResourceGroupManager::getSingleton().addResourceLocation("./Media/Particle", "FileSystem", "Particle");
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	// Set up frame listener
	WindowEventUtilities::addWindowEventListener(mWindow, this);
}

Renderer::~Renderer ()
{
	delete mRoot;
}

void Renderer::renderOneFrame ()
{
	Ogre::WindowEventUtilities::messagePump();
	mRoot->renderOneFrame();
}

Camera* Renderer::switchCamera (Camera* camera)
{
	assert(camera);
	assert(mWindow);
	assert(mSceneManager);

	Camera* prevCamera = mCamera;
	mCamera = camera;
	if (mViewport)
		mWindow->removeViewport(0);

	mViewport = mWindow->addViewport(mCamera, 0);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAutoAspectRatio(true);

	return prevCamera;
}

void Renderer::destroyCamera ()
{
	assert(mWindow);
	assert(mSceneManager);
	assert(mCamera);

	mWindow->removeViewport(0);
	mViewport = nullptr;

	mSceneManager->destroyCamera(mCamera);
	mCamera = nullptr;
}

Ogre::Root* Renderer::getRoot ()
{
	return mRoot;
}

Ogre::RenderWindow* Renderer::getRenderWindow()
{
	return mWindow;
}

Ogre::SceneManager* Renderer::getSceneManager ()
{
	return mSceneManager;
}

void selectRenderSystem (Root* root)
{
	// Select render system
	const RenderSystemList &renderers = root->getAvailableRenderers();
	RenderSystem* renderSystem = nullptr;
	LogManager::getSingletonPtr()->logMessage("Getting available renderers");
	for (auto renderer = renderers.begin(); renderer != renderers.end(); renderer++)
	{
		String name = (*renderer)->getName();
		LogManager::getSingletonPtr()->logMessage(name);
		renderSystem = *renderer;
	}
	if (renderSystem)
	{
		LogManager::getSingletonPtr()->logMessage("Using renderer " + renderSystem->getName());
		root->setRenderSystem(renderSystem);
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage(LML_CRITICAL, "Initializing render system failed. No renderers available.");
	}
}

void Renderer::windowClosed (Ogre::RenderWindow *rw) 
{
	mRunning = false;
}
