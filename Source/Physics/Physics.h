#pragma once

#include <OgreSceneManager.h>
#include "OgreBulletDynamicsWorld.h"
#include "Module.h"

class Physics : public Module
{
public:
	Physics(Ogre::SceneManager* sceneMgr);
	~Physics();

private:
	OgreBulletDynamics::DynamicsWorld* mWorld = nullptr;
};
