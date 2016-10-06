#pragma once

class Entity;

class Component
{
public:

// PUBLIC API
	Component () {}
	virtual ~Component () {}

	virtual void update () {}

	// Modifiers //
	// When enabled and loaded, update is called every tick - Components begin enabled
	void enable();
	void disable();

	// State //
	Entity* getEntity();

	bool isLoaded();
	bool isEnabled();

// RESTRICTED API
	// Callbacks called when loaded/unloaded by an Entity
	// Used by Entity
	void onLoad(Entity* entity);
	void onUnload(Entity* entity);

protected:
	// Called in onLoad(), before being added to the list of enabled components
	// Use this for processing immediately after being added to an entity
	virtual void onLoadCallback(Entity* entity) {}

private:
	bool mLoaded = false;
	bool mEnabled = true;
	Entity* mEntity = nullptr;
};