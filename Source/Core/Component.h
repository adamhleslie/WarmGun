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
	void startUpdating();
	void stopUpdating();

	// State //
	Entity* getEntity();

	bool isLoaded();
	bool isUpdating();

// RESTRICTED API
	// Callbacks called when loaded/unloaded by an Entity
	// Used by Entity
	void onLoad(Entity* entity);
	void onUnload(Entity* entity);

protected:
	// Called after being loaded/before being unloaded by an entity
	virtual void postLoad () {};
	virtual void preUnload () {};

private:
	bool mLoaded = false;
	bool mUpdating = true;
	Entity* mEntity = nullptr;
};