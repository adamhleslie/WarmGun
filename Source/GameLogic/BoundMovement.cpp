#include "BoundMovement.h"

#include <cstdlib>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "Transform.h"
#include "Entity.h"

using Ogre::Vector3;

void BoundMovement::update ()
{
	Ogre::SceneNode* ballNode = getEntity()->getTransform()->getSceneNode();
	Vector3 initial = ballNode->getPosition();

	Vector3 next = initial + mBallVelocity;

	if (mBallVelocity.x >= 0 && (next.x + mBallRadius > mWallDistances.x) ||
		mBallVelocity.x <= 0 && (next.x - mBallRadius < -mWallDistances.x))
	{
			mBallVelocity.x = -mBallVelocity.x;
	}

	if (mBallVelocity.y >= 0 && (next.y + mBallRadius > mWallDistances.y) ||
		mBallVelocity.y <= 0 && (next.y - mBallRadius < -mWallDistances.y))
	{
			mBallVelocity.y = -mBallVelocity.y;
	}

	if (mBallVelocity.z >= 0 && (next.z + mBallRadius > mWallDistances.z) ||
		mBallVelocity.z <= 0 && (next.z - mBallRadius < -mWallDistances.z))
	{
			mBallVelocity.z = -mBallVelocity.z;
	}

	ballNode->translate(mBallVelocity);
}