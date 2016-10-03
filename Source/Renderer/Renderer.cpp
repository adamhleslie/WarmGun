#include "Renderer.h"

#include "CoreConfig.h"

using namespace Ogre;

void selectRenderSystem(Root* root);

Renderer::Renderer ()
{
	mRoot = new Root("");
	// Load Plugins
#if _DEBUG
	mRoot->loadPlugin("RenderSystem_GL_d");
#else
	mRoot->loadPlugin("RenderSystem_GL");
#endif



	// Initialize with render system
	selectRenderSystem(mRoot);
	//TODO: change back to false to stop autocreating window
	mRoot->initialise(true);

	// Create scene manager, render window, and camera
	//mWindow = mRoot->createRenderWindow(PROJECT_NAME, 640, 480, false);
	mWindow = mRoot->getAutoCreatedWindow ();

	// Load in resources
	ResourceGroupManager::getSingleton().addResourceLocation("./Media", "FileSystem", "General");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/imagesets", "FileSystem", "Imagesets");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/fonts", "FileSystem", "Fonts");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/schemes", "FileSystem", "Schemes");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/looknfeel", "FileSystem", "LookNFeel");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/layouts", "FileSystem", "Layouts");


	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	// Set up frame listener
	WindowEventUtilities::addWindowEventListener(mWindow, this);
	mWindow->addListener(this);
	mRoot->addFrameListener(this);

	disable();

	// Bootstrap CEGUI::System with an OgreRenderer object that uses the
	// default Ogre rendering window as the default output surface, an Ogre based
	// ResourceProvider, and an Ogre based ImageCodec.
	CEGUI::OgreRenderer& GUIRenderer = CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	//TODO: move
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
	quit->setText("Quit");
	quit->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

	sheet->addChild(quit);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

Renderer::~Renderer ()
{
	delete mRoot;
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

void Renderer::switchViewport (Camera* camera, int ZOrder /* = 0 */)
{
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

void Renderer::windowClosed (Ogre::RenderWindow *rw) 
{
	mRunning = false;
}

bool Renderer::quit(const CEGUI::EventArgs &e)
{
    return true;
}