/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
/*
OgreBulletApplication.h runs the OgreBullet
demo scenes and switch between them.
*/
#ifndef _OgreBulletApplication_H_
#define _OgreBulletApplication_H_

// Include the OgreBullet interface which includes Ogre itself
#include "OgreBulletCollisions.h"
#include "OgreBulletDynamics.h"

#include "OgreBulletListener.h"

#include <vector>

class OgreBulletApplication;

/*
The test application, based on the Ogre example application for consistency
*/
class OgreBulletApplication : public Ogre::FrameListener
{
public:
    OgreBulletApplication(std::vector<OgreBulletListener *> *bulletListeners);
    ~OgreBulletApplication();

    std::vector<OgreBulletListener *> *getScenesList() const
    { return mBulletListeners; }

protected:   
    void createFrameListener(void);
	// Add the standard resources, plus our own pack
    void setupResources(void);
	void loadResources(void);

    bool frameStarted(const Ogre::FrameEvent &evt);
    bool frameEnded(const Ogre::FrameEvent &evt);

    bool switchListener(OgreBulletListener *newListener);

protected:
    Ogre::Root *mRoot;
    Ogre::RenderWindow *mWindow;

    OIS::InputManager *mInputSystem;
    OIS::Keyboard     *mKeyboard;
    OIS::Mouse        *mMouse;

    OgreBulletListener *mBulletListener;
    std::vector <OgreBulletListener *> *mBulletListeners;
};

#endif //_OgreBulletApplication_H_

