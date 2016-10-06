#pragma once

/**
	To create a brand new module:
		0. Create a new folder for it, and add it to CMakeLists.txt with add_project_module
		1. Inherit from this class
		2. Call disable() within your constructor (or onLoadCallback) if you don't want your module to update upon load
		3. Increase kNumModules in Core::Core() (Core.cpp)
		4. Add your module to Core::loadModules() (Core.cpp)
		5. Add functionality as needed - Put related components into the modules folder
**/

class Core;

class Module
{
public:

// PUBLIC API
	Module () {}
	virtual ~Module () {}

	virtual void update () {}

	// Modifiers //
	// When enabled and loaded, update is called every tick - Modules begin enabled
	void startUpdating();
	void stopUpdating();

	// State //
	Core* getCore();
	
	bool isLoaded();
	bool isUpdating();

// RESTRICTED API
	// Callbacks called when loaded and when unloaded by Core
	// Used by Core
	void onLoad(Core* core);
	void onUnload(Core* core);

protected:
	// Called after being loaded/before being unloaded by the engine
	virtual void postLoad () {};
	virtual void preUnload () {};

private:
	bool mLoaded = false;
	bool mUpdating = true;
	Core* mCore = nullptr;
};