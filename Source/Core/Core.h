#pragma once

#include <array>
#include <vector>

class Module;
class Entity;
class Renderer;

class Core
{
public:
	Core();
	virtual ~Core();

	// Begins the game loop
	void run();

	// Enables/Disables updating of the given module
	void enableModule(Module* module);
	void disableModule(Module* module);

	/** Not currently implemented, since functinality not needed
	// Loads/Unloads the given entity, calling onLoad/onUnload on it
	// As long as the entity is loaded, core will handle its memory deallocation
	void loadEntity(Entity* entity);
	void unloadEntity(Entity* entity);
	*/	

	// Creates and loads an entity, using its default constructor
	Entity* createEntity();

	// Unloads the given entity, and deallocates its memory
	void destroyEntity(Entity* entity);

private:
	// Number of modules used, including Renderer and SceneController
	static constexpr size_t kNumModules = 2;
	static_assert(kNumModules >= 2, "Must have room for Renderer and SceneController modules");

	// The modules that are loaded (should be static, only added to by the initial call to loadModules)
	std::array<Module*, kNumModules> mModules;
	void loadModules();

	// The modules that are updated every tick
	std::vector<Module*> mEnabledModules;

	// The entities that are loaded
	// We don't have a separate container for enabled entities, since it will be easier to implement
	// parent-child relationships within a single container
	std::vector<Entity*> mEntities;

	Renderer* mRenderer = nullptr;
};
