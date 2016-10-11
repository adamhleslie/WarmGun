#pragma once

#include "Core.h"
#include "Component.h"
#include "Module.h"
#include "Entity.h"
#include "InputManager.h"

#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>




class PaddleController : public Component, public OIS::KeyListener
{
public:
	PaddleController();
	~PaddleController(){};

	//void update() override;
	void update();
	

	Ogre::Camera* mCamera = nullptr;
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);



protected:
	void postLoad() override;

private:

	Ogre::Vector3 mDirection;
	Ogre::Quaternion mRotate;

	int mTilt = 5;
	int mMove = 5;
	int test;

};
