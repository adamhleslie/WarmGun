/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
/*
GuiListener.h
-------------
A basic test framework that minimize code in each test scene listener.
*/
#ifndef _OgreBulletGuiListener_H_
#define _OgreBulletGuiListener_H_

#include <OGRE/OgreString.h>

namespace Gui3D {
    class Gui3D;
    class Panel;
    class PanelElement;
}

namespace Gorilla {
    class Screen;
    class Layer;
    class Rectangle;
}

class OgreBulletListener;

/*
The base Test class, is also able to listen for collisions and thus change the contact properties
*/
class OgreBulletGuiListener
{
public:
	// Constructor/destructor
    OgreBulletGuiListener(OgreBulletListener *listener,
                          Ogre::Viewport *viewport,
                          const Ogre::String &atlasName);

    virtual ~OgreBulletGuiListener();

    // Gui Callbacks
    void onButtonPress(Gui3D::PanelElement *element);
    bool onBoxCheck(Gui3D::PanelElement *element);

    inline Gui3D::Gui3D *getGui() const
    {
        return mGui;
    }

    inline Gui3D::Panel *getMainPanel() const
    {

    }

    void addBool(Gui3D::Panel *panel,
                 bool* value,
                 const Ogre::String &label,
                 const Ogre::Vector2 &pos);

    void setMouseVisiable(bool visiable);
    void setMousePosition(const Ogre::Vector2 &pos);
    
    void showHelp(bool show);

protected:
    Gui3D::Gui3D *mGui;

    OgreBulletListener *mListener;

    Gorilla::Screen *mScreen;
    Gorilla::Layer *mMouseLayer;
    Gorilla::Rectangle *mMousePointer;

    Ogre::Real mMouseCursorHalfWidth;
    Ogre::Real mMouseCursorHalfHeight;

};

#endif

