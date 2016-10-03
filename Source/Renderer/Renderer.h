#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderTargetListener.h>
#include <OgreMeshManager.h>

#include "Module.h"

// Renderer maintains and provides the game engines direct connections to Ogre
class Renderer : public Module, public Ogre::WindowEventListener
{
public:
	Renderer(Ogre::SceneType sceneType);
	virtual ~Renderer();

	void renderOneFrame();
	void switchViewport(Ogre::Camera* camera, int ZOrder = 0);

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSceneManager();

	bool mRunning = true;


private:
	Ogre::Root* mRoot = nullptr;
	Ogre::SceneManager* mSceneManager = nullptr;

	Ogre::RenderWindow* mWindow = nullptr;
	Ogre::Viewport* mViewport = nullptr;

	// Ogre::WindowEventListener
	virtual void windowClosed(Ogre::RenderWindow *rw) override;
};
