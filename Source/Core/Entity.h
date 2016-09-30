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

	// When enabled and loaded, update is called every tick - Entities begin enabled
	void enable();
	void disable();

	bool isLoaded();
	bool isEnabled();

	/** Not currently implemented, since functinality not needed
	// Loads/Unloads the given component, calling onLoad/onUnload on it
	// As long as the component is loaded, core will handle its memory deallocation
	void loadComponent(Component* component);
	void unloadComponent(Component* component);
	*/

	// Enables/Disables the given component (should already by loaded)
	void enableComponent(Component* component);
	void disableComponent(Component* component);

	// Creates and then loads a component of the given type, using its default constructor
	template <class C> 
	C* createComponent();

	// Unloads the component, and deallocates its memory
	void destroyComponent(Component* component);

	// Returns the first found loaded component of the given type
	template <class C> 
	C* getComponent();

private:
	// The components that are loaded
	std::vector<Component*> mComponents;

	// The components that are enabled (updated)
	std::vector<Component*> mEnabledComponents;

	bool mLoaded = false;
	bool mEnabled = true;
	Core* mCore = nullptr;
};