#include "Transform.h"

#include <cassert>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <OgreQuaternion.h>

#include "Entity.h"
#include "Core.h"
#include "Renderer.h"
#include "Physics.h"

using Ogre::Vector3;

Transform::~Transform ()
{
	removeRigidbody();
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

	mPhysics = core->getPhysics();
	assert(mPhysics);
}

void Transform::attachRigidbody (Shape shape, const Vector3& size, float mass /* = 0 */, float restitution /* = 0 */, bool customCallback /* = false */)
{
	assert(!mRigidBody);
	assert(!mCollisionShape);

	if (mass != 0)
		mKinematic = false;

	if (shape == kCube)
	{
		mCollisionShape = new btBoxShape(btVector3(btScalar(size.x), btScalar(size.y), btScalar(size.z)));
	}
	else if (shape == kSphere)
	{
		mCollisionShape = new btSphereShape(btScalar(size.x));
	}
	assert(mCollisionShape);
	btVector3 localInertia(0,0,0);
	mCollisionShape->calculateLocalInertia(btScalar(mass), localInertia);

	updateWorldTransformPosition();
	updateWorldTransformRotation();
	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, this, mCollisionShape, localInertia);
	mRigidBody = new btRigidBody(groundRBInfo);
	mRigidBody->setRestitution(restitution);

	if (customCallback)
	{
		mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	}

	mRigidBody->setUserPointer(getEntity());
	mPhysics->getWorld()->addRigidBody(mRigidBody);
}

void Transform::removeRigidbody ()
{
	if (mRigidBody)
	{
		mPhysics->getWorld()->removeRigidBody(mRigidBody);
		delete mRigidBody;
		mRigidBody = nullptr;
	}

	if (mCollisionShape)
	{
		delete mCollisionShape;
		mCollisionShape = nullptr;
	}
}

// Updates bullet with stored bullet information
void Transform::getWorldTransform (btTransform& worldTrans) const
{
	worldTrans = mWorldTrans;
}

// Updates Ogre SceneNode with bullet information
void Transform::setWorldTransform (const btTransform& worldTrans)
{
	mWorldTrans = worldTrans;

	btVector3 position = worldTrans.getOrigin();
	mNode->setPosition(position.x(), position.y(), position.z());

	btQuaternion rotation = worldTrans.getRotation();
	mNode->setOrientation(rotation.w(), rotation.x(), rotation.y(), rotation.z());
}

// Updates stored bullet information with Ogre SceneNode position
void Transform::updateWorldTransformPosition ()
{
	Vector3 position = mNode->getPosition();
	mWorldTrans.setOrigin(btVector3(position.x, position.y, position.z));
}

// Updates stored bullet information with Ogre SceneNode rotation
void Transform::updateWorldTransformRotation ()
{
	Ogre::Quaternion rotation = mNode->getOrientation();
	mWorldTrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
}

void Transform::translate (const Vector3& direction)
{
	mNode->translate(direction);

	if (mRigidBody)
	{
		updateWorldTransformPosition();
		mRigidBody->setCenterOfMassTransform(mWorldTrans);
	}
}

void Transform::rotate (const Ogre::Quaternion& rotation)
{
	Ogre::Quaternion totalRotation = rotation * mNode->getOrientation();
	mNode->setOrientation(totalRotation);

	if (mRigidBody)
	{
		updateWorldTransformRotation();
		mRigidBody->setCenterOfMassTransform(mWorldTrans);
	}
}

const Vector3& Transform::getPosition ()
{
	return mNode->getPosition();
}

const Ogre::Quaternion& Transform::getRotation ()
{
	return mNode->getOrientation();
}

void Transform::setPositionAndRotation (const Vector3& position, const Ogre::Quaternion& rotation)
{
	mNode->setPosition(position);
	mNode->setOrientation(rotation);

	if (mRigidBody)
	{
		updateWorldTransformPosition();
		updateWorldTransformRotation();
		mRigidBody->setCenterOfMassTransform(mWorldTrans);
	}
}
