#pragma once

#include "Component.h"

#include <OgreSceneManager.h>

class BoundMovement : public Component
{
public:
	BoundMovement() {}
	~BoundMovement() {}

	void update() override;

	Ogre::SceneNode* mBallNode = nullptr;
	Ogre::Camera* mCamera = nullptr;

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::Vector3 mWallDistances;

protected:
	// void onLoadCallback(Entity* entity);

private:
};
