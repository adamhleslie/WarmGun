#pragma once

#include <array>

class Module; 
class Renderer;

class Core
{
public:
	Core();
	virtual ~Core();

	void init();
	void run();

private:
	// Number of modules used, including Renderer and SceneController
	static constexpr size_t kNumModules = 2;
	static_assert(kNumModules >= 2, "Must have room for Renderer and SceneController modules");

	// The modules loaded after init()
	std::array<Module*, kNumModules> mModules;

	// Set to true after init()
	bool mInitialized = false;

	Renderer* mRenderer = nullptr;
};
