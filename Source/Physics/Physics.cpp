#include "Physics.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

Physics::Physics ()
{
	stopUpdating();

	mCollisionConfig = new btDefaultCollisionConfiguration();
	mCollisionDispatcher = new btCollisionDispatcher(mCollisionConfig);
	mOverlappingPairs = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, mOverlappingPairs, mSolver, mCollisionConfig);
}

Physics::~Physics ()
{
	delete mWorld;
	delete mSolver;
	delete mOverlappingPairs;
	delete mCollisionDispatcher;
	delete mCollisionConfig;
}

btDiscreteDynamicsWorld* Physics::getWorld ()
{
	assert(mWorld);
	return mWorld;
}