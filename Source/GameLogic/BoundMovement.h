#pragma once

#include "Component.h"

#include <OgreSceneManager.h>

class AudioPlayer;

class BoundMovement : public Component
{
public:
	BoundMovement() {}
	~BoundMovement() {}

	void update() override;

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::Vector3 mWallDistances;

protected:
	void postLoad() override;

private:
	AudioPlayer* mAudioPlayer = nullptr;
};
