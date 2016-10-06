#pragma once

#include "Component.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class Entity;

class Transform : public Component
{
public:
	Transform() { disable(); }
	~Transform() {}

	Ogre::SceneNode* getSceneNode();

protected:
	void onLoadCallback(Entity* entity);

private:
	// The SceneManager this transform is a part of
	Ogre::SceneManager* mSceneManager = nullptr;
	Ogre::SceneNode* mNode = nullptr;
};
