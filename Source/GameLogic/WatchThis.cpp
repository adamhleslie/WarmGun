#include "WatchThis.h"

#include <OgreCamera.h>
#include <OgreSceneNode.h>

#include "Entity.h"

#include "Transform.h"

void WatchThis::update()
{
	assert(mCamera);
	Ogre::Vector3 initial = getEntity()->getTransform()->getSceneNode()->getPosition();

	mCamera->lookAt(initial);
}