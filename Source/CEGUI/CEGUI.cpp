#include "GUI.h"
 
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h> //from 0.8 it's just Ogre/Renderer.h
 
class BasicTutorial7 : public BaseApplication
{
public:
    BasicTutorial7(void);
    virtual ~BasicTutorial7(void);
 
protected:
    CEGUI::OgreRenderer* mRenderer;
 
    virtual void createScene(void);
 
    virtual void createFrameListener(void);
 
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
 
    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
 
    bool quit(const CEGUI::EventArgs &e);
};
Make sure that your Basic Tutorial 7 implementation file looks like this:

BasicTutorial7 implementation
#include "BasicTutorial7.h"
 
//-------------------------------------------------------------------------------------
BasicTutorial7::BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
{
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createFrameListener(void)
{
    BaseApplication::createFrameListener();
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    return BaseApplication::frameRenderingQueued(evt);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
    return BaseApplication::keyPressed(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
    return BaseApplication::keyReleased(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
{
    return BaseApplication::mouseMoved(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mousePressed(arg, id);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mouseReleased(arg, id);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::quit(const CEGUI::EventArgs &e)
{
    return true;
}
 