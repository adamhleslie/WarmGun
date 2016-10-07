#include "BoundMovement.h"

#include <cstdlib>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "Transform.h"
#include "AudioPlayer.h"

using Ogre::Vector3;

void BoundMovement::update()
{
	Ogre::SceneNode* ballNode = getEntity()->getTransform()->getSceneNode();
	Vector3 initial = ballNode->getPosition();
	mCamera->lookAt(initial);

	Vector3 next = initial + mBallVelocity;

	if (mBallVelocity.x >= 0 && (next.x + mBallRadius > mWallDistances.x) ||
		mBallVelocity.x <= 0 && (next.x - mBallRadius < -mWallDistances.x))
	{
			mBallVelocity.x = -mBallVelocity.x;
			mAudioPlayer->playSound(1);
			mAudioPlayer->muteVolume();
	}

	if (mBallVelocity.y >= 0 && (next.y + mBallRadius > mWallDistances.y) ||
		mBallVelocity.y <= 0 && (next.y - mBallRadius < -mWallDistances.y))
	{
			mBallVelocity.y = -mBallVelocity.y;
			mAudioPlayer->playSound(2);
			mAudioPlayer->changeVolume(-30);
	}

	if (mBallVelocity.z >= 0 && (next.z + mBallRadius > mWallDistances.z) ||
		mBallVelocity.z <= 0 && (next.z - mBallRadius < -mWallDistances.z))
	{
			mBallVelocity.z = -mBallVelocity.z;
			mAudioPlayer->playSound(3);
			mAudioPlayer->changeVolume(30);
	}

	ballNode->translate(mBallVelocity);
}

void BoundMovement::postLoad ()
{
	mAudioPlayer = getEntity()->getComponent<AudioPlayer>();
	assert(mAudioPlayer);

	mAudioPlayer->playSound(4);
}