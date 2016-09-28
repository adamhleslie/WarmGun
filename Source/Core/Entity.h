#pragma once

#include <vector>

class Component;
class Core;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	// Calls update on all loaded and enabled components
	void update();

	// Called when loaded and when unloaded from the engine Core
	void onLoad(Core* core);
	void onUnload(Core* core);

	// When enabled and loaded, updated is called every tick - Entities begin enabled
	void enable();
	void disable();

	bool isLoaded();
	bool isEnabled();

	// Loads/Unloads the given component, calling onLoad/onUnload on it
	void loadComponent(Component* component);
	void unloadComponent(Component* component);

	// Enables/Disables the given component (should already by loaded)
	void enableComponent(Component* component);
	void disableComponent(Component* component);

	// Creates and loads a component of the given type to the entity, using its default constructor
	template <class C>
	T* createComponent();

	// Returns the first found loaded component of the given type
	template <class C>
	T* getComponent();

private:
	// The components that are loaded
	std::vector<Component*> mComponents;

	// The components that are enabled (updated)
	std::vector<Component*> mEnabledComponents;

	bool mLoaded = false;
	bool mEnabled = true;
	Core* mCore = nullptr;
};