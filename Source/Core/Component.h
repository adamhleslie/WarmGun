#pragma once

class Entity;

class Component
{
public:
	Component() {}
	virtual ~Component() {}

	virtual void update() {}

	// Called when loaded and when unloaded from an Entity
	void onLoad(Entity* entity);
	void onUnload(Entity* entity);

	// When enabled and loaded, update is called every tick - Components begin enabled
	void enable();
	void disable();

	bool isLoaded();
	bool isEnabled();

protected:
	// Callback called within onLoad()
	virtual void onLoadCallback() {}

private:
	bool mLoaded = false;
	bool mEnabled = true;
	Entity* mEntity = nullptr;
};