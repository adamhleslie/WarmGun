#include "Transform.h"

#include <cassert>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include "Entity.h"
#include "Core.h"
#include "Renderer.h"
#include "Physics.h"

using Ogre::Vector3;

Transform::~Transform ()
{
	if (mRigidBody)
		delete mRigidBody;

	if (mMotionState)
		delete mMotionState;

	if (mCollisionShape)
		delete mCollisionShape;
}

Ogre::SceneNode* Transform::getSceneNode ()
{
	assert(mNode);
	return mNode;
}

void Transform::postLoad ()
{
	Core* core = getEntity()->getCore();

	mSceneManager = core->getRenderer()->getSceneManager();
	assert(mSceneManager);

	mNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	assert(mNode);

	mPhysics = core->getModule<Physics>();
	assert(mPhysics);
}

void Transform::attachRigidbody(Shape shape, const Vector3& size, const Vector3& position, float mass)
{
	mMass = mass;

	if (shape == kBox)
	{
		mCollisionShape = new btBoxShape(btVector3(btScalar(size.x), btScalar(size.y), btScalar(size.z)));
	}
	assert(mCollisionShape);
	btVector3 localInertia(0,0,0);
	mCollisionShape->calculateLocalInertia(btScalar(mMass), localInertia);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(position.x, position.y, position.z));
	mMotionState = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mMass, mMotionState, mCollisionShape, localInertia);
	mRigidBody = new btRigidBody(groundRBInfo);

	mPhysics->getWorld()->addRigidBody(mRigidBody);
}