#include "Renderer.h"

#include "CoreConfig.h"

using namespace Ogre;

void selectRenderSystem(Root* root);

Renderer::Renderer ()
{
	mRoot = new Root("");
}

Renderer::~Renderer ()
{
	delete mRoot;
}

void Renderer::init ()
{
	// Load Plugins
#if _DEBUG
	mRoot->loadPlugin("RenderSystem_GL_d");
#else
	mRoot->loadPlugin("RenderSystem_GL");
#endif

	// Initialize with render system
	selectRenderSystem(mRoot);
	mRoot->initialise(false);

	// Create scene manager, render window, and camera
	mWindow = mRoot->createRenderWindow(PROJECT_NAME, 640, 480, false);

	// Load in resources
	ResourceGroupManager::getSingleton().addResourceLocation("../Media", "FileSystem", "General");
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	// Set up frame listener
	WindowEventUtilities::addWindowEventListener(mWindow, this);
	mWindow->addListener(this);
	mRoot->addFrameListener(this);

	mInitialized = true;
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

void Renderer::update ()
{
}

void Renderer::switchViewport(Camera* camera, int ZOrder /* = 0 */)
{
	assert(mInitialized);
	
	if (mViewport)
		mWindow->removeViewport(0);

	mViewport = mWindow->addViewport(camera, 0);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	camera->setAutoAspectRatio(true);
}

bool Renderer::frameRenderingQueued (const FrameEvent& evt)
{
	if (mWindow->isClosed())
	{
		return false;
	}

	if (!mRunning)
	{
		return false;
	}

	return true;
}

void Renderer::windowClosed(Ogre::RenderWindow *rw) 
{
	mRunning = false;
}
