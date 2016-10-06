/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)
 


This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "OgreBulletApplication.h"
#include "OgreBulletListener.h"

#include "OgreResourceGroupManager.h"

using namespace Ogre;

using namespace OIS;

using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// -------------------------------------------------------------------------
OgreBulletApplication::OgreBulletApplication(std::vector<OgreBulletListener *> *bulletListeners)
    : mRoot(NULL),
      mWindow(NULL),
      mInputSystem(NULL),
      mKeyboard(NULL),
      mMouse(NULL),
      mBulletListener(NULL),
      mBulletListeners(bulletListeners)
{
    assert(!mBulletListeners->empty());

    mRoot = new Ogre::Root;
}
// -------------------------------------------------------------------------
OgreBulletApplication::~OgreBulletApplication()
{ 
    if (mInputSystem || mKeyboard)
    {      
        mInputSystem->destroyInputObject(mKeyboard);
        mInputSystem->destroyInputObject(mMouse);
        InputManager::destroyInputSystem(mInputSystem);
    }

    mWindow->destroy();
    delete mWindow;
    mWindow = NULL;

    delete mRoot;
    mRoot = NULL;
}
// -------------------------------------------------------------------------
bool OgreBulletApplication::switchListener(OgreBulletListener *newListener)
{
    if (mBulletListener)
    {
        mKeyboard->setEventCallback(NULL);
        mMouse->setEventCallback(NULL);
        mBulletListener->shutdown();
    }

    newListener->init(Ogre::Root::getSingletonPtr(), mWindow, this);
    mKeyboard->setEventCallback(newListener->getInputListener());
    mMouse->setEventCallback(newListener->getInputListener());

    mBulletListener = newListener;

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletApplication::frameStarted(const Ogre::FrameEvent &evt)
{
    mMouse->capture();
    mKeyboard->capture();

    std::vector<OgreBulletListener *>::iterator it = mBulletListeners->begin();
    const std::vector<OgreBulletListener *>::iterator end = mBulletListeners->end();
    for (; it != end; ++it)
    {
        OgreBulletListener *listener = *it;
        if (*(listener->getBoolActivator()) == true ||
            mKeyboard->isKeyDown(listener->getNextKey()))
        {
            //if ((*it) !=  mBulletListener)
            {
                switchListener(listener);
            }
            break;
        }
        ++it;
    }	

    assert(mBulletListener);

    if (!mBulletListener->frameStarted(evt.timeSinceLastFrame))
    {
        mBulletListener->shutdown();
        return false;
    }
    return true;
}

// -------------------------------------------------------------------------
bool OgreBulletApplication::frameEnded(const Ogre::FrameEvent &evt)
{
    assert(mBulletListener);
    // we're running a scene, tell it that a frame's started 

    if (!mBulletListener->frameEnded(evt.timeSinceLastFrame))
    {
        mBulletListener->shutdown();
        return false;
    }
    return true; 
}

// -------------------------------------------------------------------------
void OgreBulletApplication::createFrameListener(void)
{
//    mFrameListener = 0;

    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
	OIS::ParamList pl;

    #if defined OIS_WIN32_PLATFORM
        mWindow->getCustomAttribute("WINDOW", &windowHnd);
    #elif defined OIS_LINUX_PLATFORM
        //mWindow->getCustomAttribute("GLXWINDOW", &windowHnd);
        mWindow->getCustomAttribute("WINDOW", &windowHnd);
    #endif    

    // Fill parameter list
    windowHndStr << (unsigned int) windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    // Uncomment these two lines to allow users to switch keyboards via the language bar
    //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND") ));
    //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE") ));

    mInputSystem  = InputManager::createInputSystem(pl);

    //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
    mKeyboard = static_cast<Keyboard *>(mInputSystem->createInputObject(OISKeyboard, true));
    mMouse = static_cast<Mouse *>(mInputSystem->createInputObject(OISMouse, true));

    unsigned int width, height, depth;
    int left, top;
    mWindow->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;

    switchListener(*(mBulletListeners->begin()));
    mRoot->addFrameListener(this);

}
// -------------------------------------------------------------------------
void OgreBulletApplication::setupResources(void)
{
	ResourceGroupManager *rsm = ResourceGroupManager::getSingletonPtr();
	StringVector groups = rsm->getResourceGroups();        
	FileInfoListPtr finfo =  ResourceGroupManager::getSingleton().findResourceFileInfo (
		"Bootstrap", "axes.mesh");
    const bool isSDK = (!finfo->empty()) &&
		StringUtil::startsWith (finfo->begin()->archive->getName(), "../../media/packs/ogrecore.zip", true);

    const String resName("OgreBullet");
	{
		if (std::find(groups.begin(), groups.end(), resName) == groups.end())
		{
			rsm->createResourceGroup(resName);
			String baseName;
			if (isSDK)
			{
				baseName = "../../../ogrebullet/";
			}
			else
			{
				baseName = "../../../../../ogreaddons/ogrebullet/";
			}

            rsm->addResourceLocation(baseName + "demos/Media","FileSystem", resName);
            rsm->addResourceLocation(baseName + "demos/Media/textures", "FileSystem", resName);
            rsm->addResourceLocation(baseName + "demos/Media/overlays", "FileSystem", resName);
            rsm->addResourceLocation(baseName + "demos/Media/materials", "FileSystem", resName);
            rsm->addResourceLocation(baseName + "demos/Media/models", "FileSystem", resName);

            rsm->addResourceLocation(baseName + "demos/Media/gui", "FileSystem", resName);
		}
	}
}
// -------------------------------------------------------------------------
void OgreBulletApplication::loadResources(void)
{
	ResourceGroupManager *rsm = ResourceGroupManager::getSingletonPtr();
	StringVector groups = rsm->getResourceGroups();      
	for (StringVector::iterator it = groups.begin(); it != groups.end(); ++it)
	{
		rsm->initialiseResourceGroup((*it));
	}
	// Initialise, parse scripts etc
	//ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

// -------------------------------------------------------------------------
