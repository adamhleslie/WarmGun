#pragma once

#include "Component.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

class Entity;
class Physics;
class btCollisionShape;

enum Shape
{
	kCube,
	kSphere
};

// Rendering/Physics location component - handles all interaction between Ogre and Bullet
class Transform : public Component, public btMotionState
{
public:
	Transform () {}
	~Transform();

	void attachRigidbody(Shape shape, const Ogre::Vector3& size, float mass = 0, float restitution = 0, bool customCallback = false);
	void removeRigidbody();

	void getWorldTransform(btTransform& worldTrans) const override;
	void setWorldTransform(const btTransform& worldTrans) override;

	void updateWorldTransformPosition();
	void updateWorldTransformRotation();

	void translate(const Ogre::Vector3& direction);
	void rotate(const Ogre::Quaternion& rotation);

	const Ogre::Vector3& getPosition();
	const Ogre::Quaternion& getRotation();
	void setPositionAndRotation (const Ogre::Vector3& position, const Ogre::Quaternion& rotation);

	Ogre::SceneNode* getSceneNode(); 

	btRigidBody* mRigidBody = nullptr;
	
protected:
	void postLoad() override;

private:
	// The SceneManager this transform is a part of
	Ogre::SceneManager* mSceneManager = nullptr;
	Ogre::SceneNode* mNode = nullptr;

	// Physics state
	bool mKinematic = true;

	Physics* mPhysics = nullptr;
	btCollisionShape* mCollisionShape = nullptr;
	btTransform mWorldTrans;
	btDefaultMotionState* mMotionState = nullptr;
};
