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
//#include <CEGUIOgreRenderer-0>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Module.h"

class Renderer : public Module, public Ogre::FrameListener, public Ogre::WindowEventListener, public Ogre::RenderTargetListener
{
public:
	Renderer();
	virtual ~Renderer();

	void switchViewport(Ogre::Camera* camera, int ZOrder = 0);

	Ogre::Root* mRoot = nullptr;
	bool mRunning = true;
	
private:
	Ogre::RenderWindow* mWindow = nullptr;
	Ogre::Viewport* mViewport = nullptr;

	// Ogre::FrameListener
	//virtual bool frameEnded(const Ogre::FrameEvent &evt) override;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
	//virtual bool frameStarted(const Ogre::FrameEvent &evt) override;

	// Ogre::WindowEventListener
	virtual void windowClosed(Ogre::RenderWindow *rw) override;
	//virtual bool windowClosing(Ogre::RenderWindow *rw) override;
	//virtual void windowFocusChange(Ogre::RenderWindow *rw) override;
	//virtual void windowMoved(Ogre::RenderWindow *rw) override;
	//virtual void windowResized(Ogre::RenderWindow *rw) override;
};
