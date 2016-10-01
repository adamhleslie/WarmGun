#pragma once

#include <array>
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

	// State //
	// Returns a pointer to the first found loaded M, nullptr if none
	template <class M>
	M* getModule();

// RESTRICTED API
	// Enables/Disables updating of the given module
	// Used by Module
	void enableModule(Module* module);
	void disableModule(Module* module);

private:
	// Number of modules used, including Renderer and SceneController
	static constexpr size_t kNumModules = 2;
	static_assert(kNumModules >= 2, "Must have room for Renderer and SceneController modules");

	// The modules that are loaded (static, see loadModules())
	std::array<Module*, kNumModules> mModules;

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
