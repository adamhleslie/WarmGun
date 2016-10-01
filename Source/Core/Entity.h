#pragma once

#include <vector>

class Component;
class Core;

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
	void enable();
	void disable();

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

	bool isLoaded();
	bool isEnabled();

// RESTRICTED API
	// Callbacks called when loaded/unloaded by Core
	// Used by Core
	void onLoad(Core* core);
	void onUnload(Core* core);

	// Enables/Disables the given component (should already by loaded)
	// Used by Component
	void enableComponent(Component* component);
	void disableComponent(Component* component);

private:
	// The components that are loaded
	std::vector<Component*> mComponents;

	// The components that are enabled (updated when loaded)
	std::vector<Component*> mEnabledComponents;

	bool mLoaded = false;
	bool mEnabled = true;
	Core* mCore = nullptr;

	// Loads/Unloads the given component, calling onLoad/onUnload on it
	// As long as the component is loaded, the entity will handle its memory deallocation
	void loadComponent(Component* component);
	void unloadComponent(Component* component);
};