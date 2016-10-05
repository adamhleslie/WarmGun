#pragma once

#include <vector>

class Module;
class Entity;
class Renderer;

class Core
{
public:

// PUBLIC API
	Core();
	virtual ~Core();

	// Begins the game loop
	void run();

	// Modifiers //
	// Creates and loads an entity, using its default constructor
	Entity* createEntity();

	// Unloads the given entity, and deallocates its memory
	void destroyEntity(Entity* entity);

	// Unloads and deallocates memory for all entities
	void destroyAllEntities();

	// State //
	// Returns a pointer to the first found loaded M (deriving from Module), nullptr if none
	template <class M>
	M* getModule();

	Renderer* getRenderer();

// RESTRICTED API
	// Enables/Disables updating of the given module
	// Used by Module
	void enableModule(Module* module);
	void disableModule(Module* module);

private:
	// The modules that are loaded (static, see loadModules())
	std::vector<Module*> mModules;

	// The modules that are loaded and enabled, updated every tick
	std::vector<Module*> mEnabledModules;

	// The entities that are loaded
	// We don't have a separate container for enabled entities, since it will be easier to implement
	// parent-child relationships within a single container
	std::vector<Entity*> mEntities;

	Renderer* mRenderer = nullptr;

	// Initialization function for loading the static modules
	void loadModules();
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