#pragma once

class Module
{
public:
	Module () {}
	virtual ~Module () {}

	virtual void init() = 0;
	virtual void update() = 0;

	bool mInitialized = false;
};