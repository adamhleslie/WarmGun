#pragma once

#include "Component.h"
#include "Module.h"
#include "Core.h"
#include "InputManager.h"

#include <OgreSceneManager.h>



class PaddleController : public Component
{
public:
	PaddleController() {}
	~PaddleController() {}

	void update() override;
	

	Ogre::Camera* mCamera = nullptr;



protected:
	void postLoad() override;

private:

	Ogre::Vector3 mDirection;
	Ogre::Vector3 mRotate;

	int mTilt = 10;
	int mMove = 10;

};
