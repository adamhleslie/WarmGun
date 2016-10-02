#include "BoundMovement.h"

#include <cstdlib>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>

using Ogre::Vector3;

void BoundMovement::update()
{
	Vector3 initial = mBallNode->getPosition();
	mCamera->lookAt(initial);

	Vector3 next = initial + mBallVelocity;

	if (mBallVelocity.x >= 0 && (next.x + mBallRadius > mWallDistances.x) ||
		mBallVelocity.x <= 0 && (next.x - mBallRadius < -mWallDistances.x))
			mBallVelocity.x = -mBallVelocity.x;

	if (mBallVelocity.y >= 0 && (next.y + mBallRadius > mWallDistances.y) ||
		mBallVelocity.y <= 0 && (next.y - mBallRadius < -mWallDistances.y))
			mBallVelocity.y = -mBallVelocity.y;

	if (mBallVelocity.z >= 0 && (next.z + mBallRadius > mWallDistances.z) ||
		mBallVelocity.z <= 0 && (next.z - mBallRadius < -mWallDistances.z))
			mBallVelocity.z = -mBallVelocity.z;

	mBallNode->translate(mBallVelocity);
}

