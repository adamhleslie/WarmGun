#pragma once

#include "SceneController.h"
#include <string>

class Scene1 : public SceneController
{
public:
	// Inherits constructor
	using SceneController::SceneController;

	void update() override;
	void loadScene() override;

private:
	Ogre::SceneNode* constructWall(const Ogre::Vector3& dir, const Ogre::Vector3& up, 
								   const Ogre::Vector3& pos, const std::string& name);

	size_t mBallRadius;
	Ogre::Vector3 mBallVelocity;
	Ogre::SceneNode* mBallNode = nullptr;

	Ogre::Camera* mCamera = nullptr;

	Ogre::Vector3 mWallDistances;
};
