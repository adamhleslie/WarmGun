#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h
#include <OISKeyboard.h>
#include <OISInputManager.h>

#include "Renderer.h"
#include "CoreConfig.h"
#include "Module.h"
#include "Core.h"
#include "SceneController.h"
 
class GUI : public Module, public OIS::KeyListener
{
public:
    GUI(Ogre::RenderWindow* mWindow);
    virtual ~GUI(void);

    void update();
    void scorePoint();
    void lose();
    void clientLose();
    void serverLose();

    bool keyPressed(const OIS::KeyEvent& ke);
    bool keyReleased(const OIS::KeyEvent& ke);
 
protected:
    CEGUI::OgreRenderer* GUIRenderer;

    int mScore = 0;
    CEGUI::Window* score;

    CEGUI::Window* winBoard;
    CEGUI::Window* loseBoard;
    CEGUI::Window* replayButton;
    CEGUI::Window* howToButton;
    CEGUI::Window* howToText;
    
 
    // virtual void createFrameListener(void);
 
    // // Ogre::FrameListener
    // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
 
    // // OIS::KeyListener
    // virtual bool keyPressed( const OIS::KeyEvent &arg );
    // virtual bool keyReleased( const OIS::KeyEvent &arg );
    // // OIS::MouseListener
    // virtual bool mouseMoved( const OIS::MouseEvent &arg );
    // virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    // virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
 
    bool quit(const CEGUI::EventArgs &e);
    void createGameUI();
    void loadResources();

    void postLoad() override;
};