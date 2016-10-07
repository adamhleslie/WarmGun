/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/

#include "OgreBulletListener.h"
#include "OgreBulletInputListener.h"

using namespace Ogre;

// -------------------------------------------------------------------------
OgreBulletInputListener::OgreBulletInputListener(OgreBulletListener * ogreBulletListener, 
                                                 Ogre::RenderWindow *win)
    : mButton0Pressed(false),
      mButton1Pressed(false),
      mButton2Pressed(false),
      mWindow(win),
      mListener(ogreBulletListener),
      mMouseCursorX(0.5),
      mMouseCursorY(0.5)
{ }
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseClicked(const OIS::MouseEvent &e)
{
    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseEntered(const OIS::MouseEvent &e)
{
    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseExited(const OIS::MouseEvent &e)
{
    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mousePressed(const OIS::MouseEvent &e,
                                           OIS::MouseButtonID buttonid)
{
    if (buttonid == OIS::MB_Left)
    {
        mButton0Pressed = true;
        mListener->button0Pressed();
    }
    else if (buttonid == OIS::MB_Middle)
    {
        mButton1Pressed = true;
        mListener->button1Pressed();
    }
    else if (buttonid == OIS::MB_Right)
    {
        mButton2Pressed = true;
        mListener->button2Pressed();
    }

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseReleased(const OIS::MouseEvent &e,
                                            OIS::MouseButtonID buttonid)
{
    if (buttonid == OIS::MB_Left)
    {
        mButton0Pressed = false;
        mListener->button0Released();
    }

    if (buttonid == OIS::MB_Middle)
    {
        mButton1Pressed = false;
        mListener->button1Released();
    }

    if (buttonid == OIS::MB_Right)
    {
        mButton2Pressed = false;
        mListener->button2Released();
    }

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseDragged(const OIS::MouseEvent &e)
{ 
    // This populates the cursor moves or camera rotation variables
    mRelX = e.state.X.rel;
    mRelY = e.state.Y.rel;

    mMouseCursorX = Real(e.state.X.abs) / mWindow->getWidth();
    mMouseCursorY = Real(e.state.Y.abs) / mWindow->getHeight();

    mListener->mouseMoved();

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::mouseMoved(const OIS::MouseEvent &e)
{
    // This populates the cursor moves or camera rotation variables
    mRelX = e.state.X.rel;
    mRelY = e.state.Y.rel;

    mMouseCursorX = Real(e.state.X.abs) / mWindow->getWidth();
    mMouseCursorY = Real(e.state.Y.abs) / mWindow->getHeight();

    mListener->mouseMoved();

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::keyClicked(const OIS::KeyEvent &e)
{
    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::keyPressed(const OIS::KeyEvent &e)
{
    mListener->keyPressed(e.key);
    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletInputListener::keyReleased(const OIS::KeyEvent &e)
{
    mListener->keyReleased(e.key);
    return true;
}
