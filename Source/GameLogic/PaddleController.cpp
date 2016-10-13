#include "PaddleController.h"

// #include <cstdlib>
#include <OgreCamera.h>
// #include <OgreEntity.h>
// #include <OgreSceneNode.h>

using Ogre::Vector3;

PaddleController::PaddleController(){
  mDirection = Ogre::Vector3(0, 0, 0);
  mRotate = Ogre::Quaternion(1, 1, 1, 1);
}

void PaddleController::postLoad(){

  getEntity()->getCore()->getModule<InputManager>()->addKeyListener( this, "PaddleKeyListener" );
}

void PaddleController::update(){
  Transform* transform = getEntity()->getComponent<Transform>();
  transform->translate(mDirection);
  mCamera->move(mDirection);
  transform->rotate(mRotate);
}

bool PaddleController::keyPressed(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {
  case OIS::KC_ESCAPE:
    getEntity()->getCore()->getRenderer()->mRunning = false;
    break;
 

  case OIS::KC_A:
    mDirection.x = mMove;
    break;
 
  case OIS::KC_D:
    mDirection.x = -mMove;
    break;

  case OIS::KC_W:
    mDirection.z = mMove;
    break;

  case OIS::KC_S:
    mDirection.z = -mMove;
    break;


  case OIS::KC_UP:
    mRotate.z = -mTilt;
    break;

  case OIS::KC_DOWN:
    mRotate.z = mTilt;
    break;
 
  case OIS::KC_LEFT:
    mRotate.x = -mTilt;
    break;

  case OIS::KC_RIGHT:
    mRotate.x = mTilt;
    break;

  case OIS::KC_P:
    ap->muteBackgroundMusic();
    break;
 
  // case OIS::KC_PGDOWN:
  // case OIS::KC_E:
  //   mDirection.y = -mMove;
  //   break;
 
  // case OIS::KC_PGUP:
  // case OIS::KC_Q:
  //   mDirection.y = mMove;
  //   break;
 
  default:
    break;
  }
 
  return true;
}
 
bool PaddleController::keyReleased(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {


  case OIS::KC_A:
    mDirection.x = 0;
    break;

  case OIS::KC_D:
    mDirection.x = 0;
    break;

  case OIS::KC_W:
    mDirection.z = 0;
    break;

  case OIS::KC_S:
    mDirection.z = 0;
    break;
 

  case OIS::KC_UP:
    mRotate.z = 0;
    break;

  case OIS::KC_DOWN:
    mRotate.z = 0;
    break;

  case OIS::KC_LEFT:
    mRotate.x = 0;
 
  case OIS::KC_RIGHT:
    mRotate.x = 0;
    break;


 
  // case OIS::KC_PGDOWN:
  //  //tilt
  //   break;

  // case OIS::KC_E:
  //   mDirection.y = 0;
  //   break;
 
  // case OIS::KC_PGUP:
  //  //tilt
  //   break;

  // case OIS::KC_Q:
  //   mDirection.y = 0;
  //   break;
 
  default:
    break;
  }
 
  return true;
}