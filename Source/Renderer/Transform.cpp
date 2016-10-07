#include "Transform.h"

#include <cassert>

#include "Entity.h"
#include "Core.h"
#include "Renderer.h"

Ogre::SceneNode* Transform::getSceneNode ()
{
	assert(mNode);
	return mNode;
}

void Transform::postLoad ()
{
	Entity* entity = getEntity();

	mSceneManager = entity->getCore()->getRenderer()->getSceneManager();
	assert(mSceneManager);

	mNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	assert(mNode);
}