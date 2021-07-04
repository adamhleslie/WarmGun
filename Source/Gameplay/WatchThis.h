#pragma once

#include "Component.h"

#include <OgreSceneManager.h>

class WatchThis : public Component
{
public:
	WatchThis () {}
	~WatchThis () {}

	void update() override;

	Ogre::Camera* mCamera = nullptr;
};
