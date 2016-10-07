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

	Ogre::Camera* mCamera = nullptr;

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::Vector3 mWallDistances;

protected:
	void onLoadCallback(Entity* entity) override;

private:
	AudioPlayer* mAudioPlayer = nullptr;
};
