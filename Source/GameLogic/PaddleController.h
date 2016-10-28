#pragma once

#include "Core.h"
#include "Component.h"
#include "Module.h"
#include "Entity.h"
#include "InputManager.h"
#include "AudioPlayer.h"

#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>

class PaddleController : public Component, public OIS::KeyListener
{
public:
	PaddleController();
	~PaddleController () {};

	//void update() override;
	void update();

	AudioPlayer* ap = nullptr;
	Ogre::Camera* mCamera = nullptr;
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

protected:
	void postLoad() override;

private:
	Ogre::Vector3 mDirection;
	Ogre::Quaternion mRotate;

	float mTilt = 1;
	float mMove = .25;
};
