#pragma once

#include "Component.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>

class Entity;
class Physics;
class btCollisionShape;
class btDefaultMotionState;
class btRigidBody;

enum Shape
{
	kBox,
	kBox2D
};

class Transform : public Component
{
public:
	Transform() {  }
	~Transform();

	void attachRigidbody(Shape shape, const Ogre::Vector3& size, float mass, float restitution);
	void removeRigidbody();
	// void translate();
	// void rotate();
	// void applyForce();

	void synchronizeSceneNode();

	Ogre::SceneNode* getSceneNode(); 

protected:
	void postLoad() override;

private:
	// The SceneManager this transform is a part of
	Ogre::SceneManager* mSceneManager = nullptr;
	Ogre::SceneNode* mNode = nullptr;

	// Physics state
	Physics* mPhysics = nullptr;
	float mMass = 0;
	btCollisionShape* mCollisionShape = nullptr;
	btDefaultMotionState* mMotionState = nullptr;
	btRigidBody* mRigidBody = nullptr;
};
