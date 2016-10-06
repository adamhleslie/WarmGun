/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
/*
InputListener.h
-------------
A basic test framework that minimize code in each test scene listener.
*/
#ifndef _OgreBulletInputListener_H_
#define _OgreBulletInputListener_H_

#include "Ogre.h"

#include <OIS.h>

namespace OIS
{
    class Keyboard;
    class Mouse;
}

#define BULLET_KEY_CODE                             OIS::KeyCode

#define BULLET_GETKEY       e.key

#define BULLET_BUTTON0_DOWN buttonid == OIS::MB_Left
#define BULLET_BUTTON1_DOWN buttonid == OIS::MB_Middle
#define BULLET_BUTTON2_DOWN buttonid == OIS::MB_Right

#define BULLET_BUTTON0_UP buttonid == OIS::MB_Left
#define BULLET_BUTTON1_UP buttonid == OIS::MB_Middle
#define BULLET_BUTTON2_UP buttonid == OIS::MB_Right

#define BULLET_GETRELX      e.state.X.rel
#define BULLET_GETRELY      e.state.Y.rel

#define BULLET_GETX         e.state.X.abs
#define BULLET_GETY         e.state.Y.abs

#include "OgreBulletGuiListener.h"
class OgreBulletListener;

/*
The base Test class, is also able to listen for collisions and thus change the contact properties
*/
class OgreBulletInputListener : public OIS::MouseListener, public OIS::KeyListener
{
public:
    static const Ogre::Real KEY_DELAY;

    OgreBulletInputListener(OgreBulletListener *ogreBulletListener,
                            Ogre::RenderWindow *win);

    virtual ~OgreBulletInputListener() { }

    // MouseMotionListener Callbacks
    bool mouseDragged(const OIS::MouseEvent &e);
    bool mouseMoved(const OIS::MouseEvent &e);

    // MouseListener Callbacks
    bool mouseClicked(const OIS::MouseEvent &e);
    bool mouseEntered(const OIS::MouseEvent &e);
    bool mouseExited(const OIS::MouseEvent &e);

    bool mousePressed(const OIS::MouseEvent &e,
                      OIS::MouseButtonID buttonid);

    bool mouseReleased(const OIS::MouseEvent &e,
                       OIS::MouseButtonID buttonid);

    // KeyListener Callbacks
    bool keyClicked(const OIS::KeyEvent &e);
    bool keyPressed(const OIS::KeyEvent &e);
    bool keyReleased(const OIS::KeyEvent &e);

    inline Ogre::Real getRelMouseX() const { return mRelX; }
    inline Ogre::Real getRelMouseY() const { return mRelY; }

    inline Ogre::Real getAbsMouseX() const { return mMouseCursorX; }
    inline Ogre::Real getAbsMouseY() const { return mMouseCursorY; }

    inline bool getButton0Pressed() const { return mButton0Pressed; }
    inline bool getButton1Pressed() const { return mButton1Pressed; }
    inline bool getButton2Pressed() const { return mButton2Pressed; }

protected:
    Ogre::Real mRelX;
    Ogre::Real mRelY;
    Ogre::Real mMouseCursorX;
    Ogre::Real mMouseCursorY;

    bool mButton0Pressed;
    bool mButton1Pressed;
    bool mButton2Pressed;

    Ogre::RenderWindow *mWindow;
    OgreBulletListener *mListener;
};

#endif

