#ifndef InputManager_H
#define InputManager_H
 
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>

// #include <CEGUI/CEGUI.h>
// #include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <SdkCameraMan.h>


#include <OgreRenderWindow.h>
#include "Renderer.h"

#include "CoreConfig.h"

#include "Module.h"
 
class InputManager : public OIS::KeyListener, public OIS::MouseListener, public Module {
public:
    InputManager(Ogre::RenderWindow *renderWindow);
    virtual ~InputManager( void );
 
    void initialise( Ogre::RenderWindow *renderWindow );
    void update( void );
    void setCameraMan(OgreBites::SdkCameraMan* cameraMan);
    void setScreenSize(int width, int height);
 
    void addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName );
    void addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName );
 
    void removeKeyListener( const std::string& instanceName );
    void removeMouseListener( const std::string& instanceName );
 
    void removeKeyListener( OIS::KeyListener *keyListener );
    void removeMouseListener( OIS::MouseListener *mouseListener );
 
    void removeAllListeners( void );
    void removeAllKeyListeners( void );
    void removeAllMouseListeners( void );
 
    void setWindowExtents( int width, int height );
 
    OIS::Mouse*    getMouse( void );
    OIS::Keyboard* getKeyboard( void );

    OgreBites::SdkCameraMan * mCameraMan;
  
    static InputManager* getSingletonPtr( void );

    int getMouseXAxis();
    int getMouseYAxis();
    OIS::KeyCode getKeyPressed();
    OIS::KeyCode lastKeyPressed();

private:
    InputManager( void );
    InputManager( const InputManager& ) { }
    InputManager & operator = ( const InputManager& );
 
    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );
 
    bool mouseMoved( const OIS::MouseEvent &e );
    bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );
 
    OIS::Mouse        *mMouse;
    OIS::Keyboard     *mKeyboard;
    OIS::InputManager *mInputSystem;

    // CEGUI::MouseButton convertButton(OIS::MouseButtonID);
 
    std::map<std::string, OIS::KeyListener*> mKeyListeners;
    std::map<std::string, OIS::MouseListener*> mMouseListeners;
 
    std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
    std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
 
    std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
    std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
 
    static InputManager *mInputManager;

    int mouseXAxis;
    int mouseYAxis;
    OIS::KeyCode mKeyPressed;
};
#endif