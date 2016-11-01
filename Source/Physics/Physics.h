#pragma once

#include "Module.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class GUI;
class NetManager;

class Physics : public Module
{
public:
	Physics(GUI* gui, NetManager* netMgr);
	~Physics();

	btDiscreteDynamicsWorld* getWorld();

private:
	btDefaultCollisionConfiguration* mCollisionConfig = nullptr;
	btCollisionDispatcher* mCollisionDispatcher = nullptr;
	btBroadphaseInterface* mOverlappingPairs = nullptr;
	btSequentialImpulseConstraintSolver* mSolver = nullptr;
	btDiscreteDynamicsWorld* mWorld = nullptr;
};