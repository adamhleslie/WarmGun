#include <iostream>
#include "GUI.h"
 
 using namespace Ogre;
//-------------------------------------------------------------------------------------
GUI::GUI(Ogre::RenderWindow* mWindow)
{
	stopUpdating();

		//this.mRoot = mRoot;
	CEGUI::OgreRenderer& GUIRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


	// Load in resources
	loadResources();



	// CEGUI::FontManager &fmg = CEGUI::FontManager::getSingleton();
	// CEGUI::Font &font = fmg.createFreeTypeFont("arial", 20, true, "arial.ttf");
	//CEGUI::Font &font = fmg.createFreeTypeFont("futhark adapted", 20, true, "FutharkAdapted.ttf");
	
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "GameUI");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

	CEGUI::Window* quitButton = wmgr.createWindow("AlfiskoSkin/Button", "QuitButton");
	quitButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.0f, 0), CEGUI::UDim(0.0f, 0)),
		CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.05f, 0))));
	quitButton->setText("ESC = quit");

	replayButton = wmgr.createWindow("AlfiskoSkin/Button", "ReplayButton");
	replayButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.4f, 0)),
		CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.45f, 0))));
	replayButton->setText("Replay");


	// howToButton = wmgr.createWindow("AlfiskoSkin/Button", "HowToButton");
	// howToButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.3f, 0)),
	//     CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.35f, 0))));
	// howToButton->setText("How To Play");

	// howToText = wmgr.createWindow("AlfiskoSkin/MultiLineEditbox", "Instructions");
	// howToText->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.125f, 0), CEGUI::UDim(0.35f, 0)),
	//     CEGUI::UVector2(CEGUI::UDim(0.875f, 0), CEGUI::UDim(0.75f, 0))));
	// howToText->setText(instructions);
	// static_cast<CEGUI::MultiLineEditbox*>(howToText)->setReadOnly(true);




	sheet->addChild(quitButton);
	sheet->addChild(replayButton);
	// sheet->addChild(howToButton);
	// sheet->addChild(howToText);

	replayButton->hide();

	//***********************
	//quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::Quit, this));
	//replayButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::Replay, this));
	


	//howToButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::HowTo, this));


	//CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	// CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	// CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	//CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");

	// CEGUI::Window *score = wmgr.createWindow("HUDDemo/PopupLabel", "GameUI/Score");
	// score->setText("Score: ");
	// score->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

	// quit->setText("Quit");
	// quit->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	//CEGUI::OgreRenderer* mRenderer;

	// CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	// CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "GameUI/Sheet");
	//CEGUI::Window *sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow(); 

	score = wmgr.createWindow("AlfiskoSkin/Label", "Score");
	score->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.0f, 0), CEGUI::UDim(0.92f, 0)),
	CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1, 0))));
	score->setText("Score: 0");

	winBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "WinBoard");
	winBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
		CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
	winBoard->setText("     You Win!");
	//winBoard->setDisabled(true);
	winBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
	//winBoard->hide();

	// loseBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "LoseBoard");
	// loseBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
	//     CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
	// loseBoard->setText("    You Lose!");
	// loseBoard->setDisabled(true);
	// loseBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
	// loseBoard->hide();

	sheet->addChild(score);
	// sheet->addChild(winBoard);
	// sheet->addChild(loseBoard);

	// sheet->addChild(score);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}
//-------------------------------------------------------------------------------------
GUI::~GUI(void)
{
}
//-------------------------------------------------------------------------------------

void GUI::createGameUI(void)
{
	//BaseApplication::createFrameListener();
}

void GUI::scorePoint()
{
	mScore += 1;
	score->setText("Score: " + std::to_string(mScore));
}

void GUI::lose()
{
	score->setText("DANG! Your score was " + std::to_string(mScore));
}

void GUI::loadResources()
{
		// Load in resources
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/imagesets", "FileSystem", "Imagesets");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/fonts", "FileSystem", "Fonts");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/schemes", "FileSystem", "Schemes");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/looknfeel", "FileSystem", "LookNFeel");
	ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/layouts", "FileSystem", "Layouts");

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("HUDDemo.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
}

//-------------------------------------------------------------------------------------
// bool GUI::frameRenderingQueued(const Ogre::FrameEvent& evt)
// {
//     return BaseApplication::frameRenderingQueued(evt);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::keyPressed( const OIS::KeyEvent &arg )
// {
//     return BaseApplication::keyPressed(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::keyReleased( const OIS::KeyEvent &arg )
// {
//     return BaseApplication::keyReleased(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mouseMoved( const OIS::MouseEvent &arg )
// {
//     return BaseApplication::mouseMoved(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
// {
//     return BaseApplication::mousePressed(arg, id);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
// {
//     return BaseApplication::mouseReleased(arg, id);
// }
//-------------------------------------------------------------------------------------
bool GUI::quit(const CEGUI::EventArgs &e)
{
	return true;
}

void GUI::postLoad ()
{
	getCore()->getModule<InputManager>()->addKeyListener(this, "GUIKeyListener");
}

void GUI::update ()
{
}

bool GUI::keyPressed (const OIS::KeyEvent& ke)
{
	return true;
}

bool GUI::keyReleased (const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
		// Special keys
		case OIS::KC_ESCAPE:
			getCore()->getRenderer()->mRunning = false;
			break;

		case OIS::KC_UP:
			getCore()->getModule<InputManager>()->removeKeyListener(this);
			getCore()->getModule<SceneController>()->initSingleplayer();
			break;

		default:
			break;
	}

	return true;
}