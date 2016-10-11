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

void Transform::attachRigidbody (Shape shape, const Vector3& size, float mass /* = 0 */, float restitution /* = 0 */)
{
	assert(!mRigidBody);
	assert(!mMotionState);
	assert(!mCollisionShape);
	mMass = mass;

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

	btTransform transform;
	transform.setIdentity();

	Vector3 position = mNode->getPosition();
	transform.setOrigin(btVector3(position.x, position.y, position.z));

	Ogre::Quaternion rotation = mNode->getOrientation();
	transform.setRotation(btQuaternion(rotation.w, rotation.x, rotation.y, rotation.z));

	mMotionState = new btDefaultMotionState(transform);
	mCollisionShape->calculateLocalInertia(btScalar(mMass), localInertia);

	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mMass, mMotionState, mCollisionShape, localInertia);
	mRigidBody = new btRigidBody(groundRBInfo);
	mRigidBody->setRestitution(restitution);

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

	if (mMotionState)
	{
		delete mMotionState;
		mMotionState = nullptr;
	}

	if (mCollisionShape)
	{
		delete mCollisionShape;
		mCollisionShape = nullptr;
	}
}

void Transform::synchronizeSceneNode ()
{
	if (mRigidBody)
	{
		btTransform trans;
		mRigidBody->getMotionState()->getWorldTransform(trans);

		btVector3 position = trans.getOrigin();
		mNode->setPosition(position.getX(), position.getY(), position.getZ());

		btQuaternion orientation = trans.getRotation();
		mNode->setOrientation(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ());
	}
}

void Transform::translate(const Ogre::Vector3 &direction){
	// btTransform transform;
	// transform.setIdentity();
	mRigidBody->translate(btVector3(direction.x, direction.y, direction.z));
	synchronizeSceneNode ();
}

void Transform::rotate(const Ogre::Quaternion& rotation){
	btMatrix3x3 orn = mRigidBody->getWorldTransform().getBasis(); //get basis of world transformation
  	orn *= btMatrix3x3(btQuaternion(rotation.w, rotation.x, rotation.y, rotation.z));     //Multiply it by rotation matrix
 	mRigidBody->getWorldTransform().setBasis(orn); //set new rotation for the object

	// transform.setRotation(btQuaternion(rotation.w, rotation.x, rotation.y, rotation.z));

	// mRigidBody->setCenterOfMassTransform(transform);
	synchronizeSceneNode ();
}