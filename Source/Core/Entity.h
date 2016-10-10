#pragma once

#include <vector>

class Component;
class Core;
class Transform;

class Entity
{
public:

// PUBLIC API
	Entity() {}
	~Entity();

	// Calls update on all loaded components that are enabled
	void update();

	// Modifiers //
	// When enabled and loaded, update is called every tick - Entities begin enabled
	void startUpdating();
	void stopUpdating();

	// Creates and then loads a component of the given type, using its default constructor
	template <class C> 
	C* createComponent();

	// Unloads the component, and deallocates its memory
	void destroyComponent(Component* component);

	// State //
	// Returns the first found loaded component of the given type, nullptr if none
	template <class C> 
	C* getComponent();

	Core* getCore();
	Transform* getTransform();

	bool isLoaded();
	bool isUpdating();

// RESTRICTED API
	// Callbacks called when loaded/unloaded by Core
	// Used by Core
	void onLoad(Core* core);
	void onUnload(Core* core);

	// Enables/Disables the given component (should already by loaded)
	// Used by Component
	void startUpdatingComponent(Component* component);
	void stopUpdatingComponent(Component* component);

// 	//BBPW
// 	BulletContactCallback* cCallBack;

// protected:

// 	//ball, brick, paddle, wall (BBPW) variables START
// 	Ogre::String name; //TODO: do we also need a type?
// 	Ogre::Entity* geometry;
// 	Ogre::Real scale;
// 	Ogre::Vector3 vscale;
// 	Ogre::Vector3 startPos;
// 	OgreMotionState* motionState;

// 	//TODO: Need a renderer or gamelogic object?
// 	btCollisionShape* shape;
// 	btRigidBody* body;
// 	btTransform bulletTransform;
// 	btVector3 inertia;

// 	bool exploded;

// 	CollisionContext* context;

// 	btScalar mass;
// 	btScalar friction;
// 	btScalar restitution;

// 	bool needsUpdates;

// 	Ogre::ParticleSystem* particle;
// 	//BBPW END

private:
	// The components that are loaded
	std::vector<Component*> mComponents;

	// The components that are enabled (updated when loaded)
	std::vector<Component*> mUpdatingComponents;

	Core* mCore = nullptr;
	Transform* mTransform = nullptr;

	bool mLoaded = false;
	bool mUpdating = true;

	// Loads/Unloads the given component, calling onLoad/onUnload on it
	// As long as the component is loaded, the entity will handle its memory deallocation
	void loadComponent(Component* component);
	void unloadComponent(Component* component, bool findAndRemove = true);

	// Creates the components every entity has (Transform, ...)
	void createDefaultComponents();
};

// Template Methods //
#include <type_traits>

template <class C> 
C* Entity::createComponent ()
{
	static_assert(std::is_base_of<Component, C>::value, 
				  "createComponent: templated type must be derived from Component");
	
	C* component = new C();
	Component* casted = static_cast<Component*>(component);
	loadComponent(casted);

	return component;
}

template <class C> 
C* Entity::getComponent ()
{
	static_assert(std::is_base_of<Component, C>::value, 
				  "getComponent: templated type must be derived from Component");
	
	for (Component* component : mComponents)
	{
		C* casted = dynamic_cast<C*>(component);
		if (casted)
			return casted;
	}

	return nullptr;
}