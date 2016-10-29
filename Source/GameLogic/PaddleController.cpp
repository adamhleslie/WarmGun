#include "PaddleController.h"

#include <OgreCamera.h>

using Ogre::Vector3;

PaddleController::PaddleController ()
{
	mDirection = Vector3(0, 0, 0);
	mRotate = Ogre::Quaternion::IDENTITY;
}

void PaddleController::postLoad ()
{
	getEntity()->getCore()->getModule<InputManager>()->addKeyListener(this, "PaddleKeyListener");
}

void PaddleController::update ()
{
	Transform* transform = getEntity()->getComponent<Transform>();
	transform->translate(mDirection);
	mCamera->move(mDirection);
		
	Ogre::Quaternion rotation = Ogre::Quaternion::IDENTITY;
	if (mRotate.x == mRotate.z)
	{
		if (mRotate.x != 0)
		{
			// Both non-zero
			rotation = Ogre::Quaternion(Ogre::Degree(mRotate.x), Vector3(-1, 0, 1));
		}
	}
	else if (mRotate.x == 0)
	{
		// z non-zero
		rotation = Ogre::Quaternion(Ogre::Degree(mRotate.z), Vector3(0, 0, 1));
	}
	else if (mRotate.z == 0)
	{
		// x non-zero
		rotation = Ogre::Quaternion(Ogre::Degree(mRotate.x), Vector3(-1, 0, 0));
	}
	else
	{
		// both non-zero and different
		rotation = Ogre::Quaternion(Ogre::Degree(mRotate.x), Vector3(-1, 0, -1));
	}
	transform->rotate(rotation);
}

bool PaddleController::keyPressed (const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
		// Special keys
		case OIS::KC_ESCAPE:
			getEntity()->getCore()->getRenderer()->mRunning = false;
			break;

		case OIS::KC_P:
			ap->muteBackgroundMusic();
			break;

		// Translation
		case OIS::KC_A:
			mDirection.x += mMove;
			break;

		case OIS::KC_D:
			mDirection.x -= mMove;
			break;

		case OIS::KC_W:
			mDirection.z += mMove;
			break;

		case OIS::KC_S:
			mDirection.z -= mMove;
			break;

		// Rotation
		case OIS::KC_UP:
			mRotate.x -= mTilt;
			break;

		case OIS::KC_DOWN:
			mRotate.x += mTilt;
			break;

		case OIS::KC_LEFT:
			mRotate.z -= mTilt;
			break;

		case OIS::KC_RIGHT:
			mRotate.z += mTilt;
			break;


		default:
			break;
	}

	return true;
}
 
bool PaddleController::keyReleased (const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
		// Translation
		case OIS::KC_A:
			mDirection.x -= mMove;
			break;

		case OIS::KC_D:
			mDirection.x += mMove;
			break;

		case OIS::KC_W:
			mDirection.z -= mMove;
			break;

		case OIS::KC_S:
			mDirection.z += mMove;
			break;
		 
		// Rotation
		case OIS::KC_UP:
			mRotate.x += mTilt;
			break;

		case OIS::KC_DOWN:
			mRotate.x -= mTilt;
			break;

		case OIS::KC_LEFT:
			mRotate.z += mTilt;
			break;
		 
		case OIS::KC_RIGHT:
			mRotate.z -= mTilt;
			break;

		 
		default:
			break;
	}
 
	return true;
}