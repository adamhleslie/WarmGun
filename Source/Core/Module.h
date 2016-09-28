#pragma once

class Core;

/**
	To create a brand new module:
		0. Create a new folder for it, and add it to CMakeLists.txt with add_project_module
		1. Inherit from this class
		2. Implement constructor and destructor
			a. Call disable() within your constructor if you don't want your module to update upon load
		3. Increase Core::kNumModules (Core.h)
		4. Add your module to Core::loadModules() (Core.cpp)
		5. Add functionality as needed - GameObjects and Components not yet implemented
**/

class Module
{
public:
	Module () {}
	virtual ~Module () {}

	virtual void update () {}

	// Functions called when loaded and when unloaded from the engine Core
	void onLoad(Core* core);
	void onUnload(Core* core);

	bool isLoaded();
	bool isEnabled();

protected:
	// Callback called within onLoad()
	virtual void onLoadCallback() {}

	// When enabled and loaded, update is called every tick - Modules start out enabled
	void enable();
	void disable();

private:
	bool mLoaded = false;
	bool mEnabled = true;
	Core* mCore = nullptr;
};