#pragma once

#include <vector>
#include "InputManager.h"

class Module;
class Entity;
class Renderer;

class Core
{
public:

// PUBLIC API
	Core();
	virtual ~Core();

	// The fixed time step taken by every tick (in ms)
	static constexpr unsigned long kTimeStep = 4;

	// Begins the game loop
	void run();

	// Modifiers //
	// Creates and loads an entity, using its default constructor
	Entity* createEntity();

	// Unloads the given entity, and deallocates its memory
	void destroyEntity(Entity* entity, bool findAndRemove = true);

	// Unloads and deallocates memory for all entities
	void destroyAllEntities();

	// State //
	// Returns a pointer to the first found loaded M (deriving from Module), nullptr if none
	template <class M>
	M* getModule();

	Renderer* getRenderer();

// RESTRICTED API
	// Enables/Disables updating of the given module, used by Module
	void startUpdatingModule(Module* module);
	void stopUpdatingModule(Module* module);

private:
	// The modules that are loaded, and those that have update called every tick
	std::vector<Module*> mModules;
	std::vector<Module*> mUpdatingModules;

	// The entities that are loaded
	// We don't have a separate container for enabled entities, for parent-child relations
	std::vector<Entity*> mEntities;

	Renderer* mRenderer = nullptr;
	InputManager* mInputMgr = nullptr;

	// Create/load the available modules
	void createModules();

	// Calls onLoad after fully loading, and onUnload before unloading
	void loadModule(Module* module);
	void unloadModule(Module* module, bool findAndRemove = true);
};

// Template Methods //
#include <type_traits>

template <class M>
M* Core::getModule()
{
	static_assert(std::is_base_of<Module, M>::value, 
			      "getModule: templated type must be derived from Module");

	for (Module* module : mModules)
	{
		M* casted = dynamic_cast<M*>(module);
		if (casted)
			return casted;
	}

	return nullptr;
}