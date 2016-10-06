#include "Physics.h"

#include <OgreAxisAlignedBox.h>

Physics::Physics (Ogre::SceneManager* sceneMgr)
{
	mWorld = new OgreBulletDynamics::DynamicsWorld(sceneMgr, Ogre::AxisAlignedBox(Ogre::Vector3 (-10000, -10000, -10000), Ogre::Vector3 (10000,  10000,  10000)), Ogre::Vector3(0,-9.81,0));
}

Physics::~Physics ()
{
	// delete mWorld; // Causes an abort from free???
}
