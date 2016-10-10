#include "InputManager.h"
 
InputManager *InputManager::mInputManager;
 
InputManager::InputManager( void ) :
    mCameraMan( 0 ),
    mMouse( 0 ),
    mKeyboard( 0 ),
    mInputSystem( 0 ) {
}

InputManager::InputManager( Ogre::RenderWindow* renderWindow ) :
    mMouse( 0 ),
    mKeyboard( 0 ),
    mInputSystem( 0 ) {
    initialise(renderWindow);
}
 
InputManager::~InputManager( void ) {
    if( mInputSystem ) {
        if( mMouse ) {
            mInputSystem->destroyInputObject( mMouse );
            mMouse = 0;
        }
 
        if( mKeyboard ) {
            mInputSystem->destroyInputObject( mKeyboard );
            mKeyboard = 0;
        }
 
 
        // If you use OIS1.0RC1 or above, uncomment this line
        // and comment the line below it
        mInputSystem->destroyInputSystem( mInputSystem );
        //mInputSystem->destroyInputSystem();
        mInputSystem = 0;
 
        // Clear Listeners
        mKeyListeners.clear();
        mMouseListeners.clear();

    }
}
 
void InputManager::initialise( Ogre::RenderWindow *renderWindow ) {
    if( !mInputSystem ) {
        // Setup basic variables
        OIS::ParamList paramList;    
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;
 
        //WINDOWS SPECIFIC?
        // // Get window handle
        renderWindow->getCustomAttribute( "WINDOW", &windowHnd );
 
        // Fill parameter list
        windowHndStr << windowHnd;
        paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );
 
        // Create inputsystem
        mInputSystem = OIS::InputManager::createInputSystem( paramList );
 
        // If possible create a buffered keyboard
        // (note: if below line doesn't compile, try:  if (mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
        //if( mInputSystem->numKeyboards() > 0 ) {
        if (mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
            mKeyboard = dynamic_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
            mKeyboard->setEventCallback( this );
        }
 
        // If possible create a buffered mouse
        // (note: if below line doesn't compile, try:  if (mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0) {
        //if( mInputSystem->numMice() > 0 ) {
        if (mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0) {
            mMouse = dynamic_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
            mMouse->setEventCallback( this );
 
            // Get window size
            unsigned int width, height, depth;
            int left, top;
            renderWindow->getMetrics( width, height, depth, left, top );
 
            // Set mouse region
            this->setWindowExtents( width, height );
        }
    }
}
 
void InputManager::update( void ) {
    //Need to capture / update each device every frame
    if( mMouse ) {
        mMouse->capture();
    }
 
    if( mKeyboard ) {
        mKeyboard->capture();
    }
 
}
 
void InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
    if( mKeyboard ) {
        // Check for duplicate items
        itKeyListener = mKeyListeners.find( instanceName );
        if( itKeyListener == mKeyListeners.end() ) {
            mKeyListeners[ instanceName ] = keyListener;
        }
        else {
            // Duplicate Item
        }
    }
}
 
void InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {
    if( mMouse ) {
        // Check for duplicate items
        itMouseListener = mMouseListeners.find( instanceName );
        if( itMouseListener == mMouseListeners.end() ) {
            mMouseListeners[ instanceName ] = mouseListener;
        }
        else {
            // Duplicate Item
        }
    }
}
 
 
void InputManager::removeKeyListener( const std::string& instanceName ) {
    // Check if item exists
    itKeyListener = mKeyListeners.find( instanceName );
    if( itKeyListener != mKeyListeners.end() ) {
        mKeyListeners.erase( itKeyListener );
    }
    else {
        // Doesn't Exist
    }
}
 
void InputManager::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mMouseListeners.find( instanceName );
    if( itMouseListener != mMouseListeners.end() ) {
        mMouseListeners.erase( itMouseListener );
    }
    else {
        // Doesn't Exist
    }
}
 

void InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            mKeyListeners.erase( itKeyListener );
            break;
        }
    }
}
 
void InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if( itMouseListener->second == mouseListener ) {
            mMouseListeners.erase( itMouseListener );
            break;
        }
    }
}
 

 
void InputManager::removeAllListeners( void ) {
    mKeyListeners.clear();
    mMouseListeners.clear();

}
 
void InputManager::removeAllKeyListeners( void ) {
    mKeyListeners.clear();
}
 
void InputManager::removeAllMouseListeners( void ) {
    mMouseListeners.clear();
}
 
 
bool InputManager::keyPressed( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyPressed( e ))
            break;
    }
 
    return true;


    // if(cameraMan) cameraMan->injectKeyDown(e);
    // mKeyPressed = e.key;

    // CEGUI::GUIContext& cxt = CEGUI::System::getSingleton().getDefaultGUIContext();
    // cxt.injectKeyDown((CEGUI::Key::Scan)e.key);
    // cxt.injectChar((CEGUI::Key::Scan)e.text);

    // return true;
}
 
bool InputManager::keyReleased( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased( e ))
            break;
    }
 
    return true;

    // if(cameraMan) cameraMan->injectKeyUp(e);
    // return true;
}


// OIS::KeyCode InputManager::lastKeyPressed() {
//     OIS::KeyCode ret = mKeyPressed;
//     mKeyPressed = OIS::KC_UNASSIGNED;
//     return ret;
// }
 
bool InputManager::mouseMoved( const OIS::MouseEvent &e ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseMoved( e ))
            break;
    }
 
    return true;

    // if(cameraMan) cameraMan->injectMouseMove(e);

    // // From -width/2 to +width/2
    // mouseXAxis = (e.state.X.abs) - e.state.width/2;
    // mouseYAxis = (e.state.Y.abs) - e.state.height/2;

    // CEGUI::System &sys = CEGUI::System::getSingleton();
    // sys.getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
    // // Scroll wheel.
    // if (e.state.Z.rel)
    //     sys.getDefaultGUIContext().injectMouseWheelChange(e.state.Z.rel / 120.0f);

    // return true;
}
 
bool InputManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mousePressed( e, id ))
            break;
    }
 
    return true;

    // CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    // if(cameraMan) cameraMan->injectMouseDown(e, id);
    // return true;
}
 
bool InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseReleased( e, id ))
            break;
    }
 
    return true;

    // CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    // if(cameraMan) cameraMan->injectMouseUp(e, id);
    // return true;
}

CEGUI::MouseButton InputManager::convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}


//Getters

InputManager* InputManager::getSingletonPtr( void ) {
    if( !mInputManager ) {
        mInputManager = new InputManager();
    }
 
    return mInputManager;
}

OIS::Mouse* InputManager::getMouse( void ) {
    return mMouse;
}
 
OIS::Keyboard* InputManager::getKeyboard( void ) {
    return mKeyboard;
}

OIS::KeyCode InputManager::getKeyPressed(){
    return mKeyPressed;
}

int InputManager::getMouseXAxis() {
    return mouseXAxis;
}

int InputManager::getMouseYAxis() {
    return mouseYAxis;
}


//Setters

//use if not auto-creating screen size
void InputManager::setScreenSize(int width, int height){
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
}

void InputManager::setCameraMan(OgreBites::SdkCameraMan* cameraMan){
    if(!mCameraMan){
        mCameraMan = cameraMan;
    }
}

void InputManager::setWindowExtents( int width, int height ) {
    // Set mouse region (if window resizes, we should alter this to reflect as well)
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
}
