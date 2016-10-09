
#include "GUI.h"
 
 using namespace Ogre;
//-------------------------------------------------------------------------------------
GUI::GUI(Ogre::RenderWindow* mWindow)
{
    stopUpdating();
    //this.mRoot = mRoot;
    CEGUI::OgreRenderer& GUIRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);

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
    CEGUI::Window* gameScoreboard;
    CEGUI::Window* youWinBoard;
    CEGUI::Window* youLoseBoard;

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "GameUI/Sheet");
    //CEGUI::Window *sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow(); 

    gameScoreboard = wmgr.createWindow("AlfiskoSkin/Label", "Score");
    gameScoreboard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.0f, 0), CEGUI::UDim(0.92f, 0)),
    CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1, 0))));
    gameScoreboard->setText("Score: 0");

    youWinBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "YouWinBoard");
    youWinBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
    youWinBoard->setText("     You Win!");
    youWinBoard->setDisabled(true);
    youWinBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
    //youWinBoard->hide();

    // youLoseBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "YouLoseBoard");
    // youLoseBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
    //     CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
    // youLoseBoard->setText("    You Lose!");
    // youLoseBoard->setDisabled(true);
    // youLoseBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
    // youLoseBoard->hide();

    sheet->addChild(gameScoreboard);
    // sheet->addChild(youWinBoard);
    // sheet->addChild(youLoseBoard);

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
 