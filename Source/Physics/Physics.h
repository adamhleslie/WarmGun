#pragma once

#include "Module.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

class Physics : public Module
{
public:
	Physics();
	~Physics();

	btDiscreteDynamicsWorld* getWorld();

private:
	btDefaultCollisionConfiguration* mCollisionConfig = nullptr;
	btCollisionDispatcher* mCollisionDispatcher = nullptr;
	btBroadphaseInterface* mOverlappingPairs = nullptr;
	btSequentialImpulseConstraintSolver* mSolver = nullptr;
	btDiscreteDynamicsWorld* mWorld = nullptr;
};