#pragma once

#include <array>
#include <vector>

class Module;
class Renderer;

class Core
{
public:
	Core();
	virtual ~Core();

	// Begins the game loop
	void run();

	// Adds and removes the specified module from those being updated
	void enableModule(Module* module);
	void disableModule(Module* module);

private:
	// Number of modules used, including Renderer and SceneController
	static constexpr size_t kNumModules = 2;
	static_assert(kNumModules >= 2, "Must have room for Renderer and SceneController modules");

	// The modules loaded by getModules()
	std::array<Module*, kNumModules> mModules;
	void getModules();

	// The modules that are updated every tick
	std::vector<Module*> mEnabledModules;

	Renderer* mRenderer = nullptr;
};
