
#include "GUI.h"
 
 using namespace Ogre;
//-------------------------------------------------------------------------------------
GUI::GUI(/*Ogre::Root* mRoot*/)
{
    disable();
    //this.mRoot = mRoot;
    CEGUI::OgreRenderer& GUIRenderer = CEGUI::OgreRenderer::bootstrapSystem();

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
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");

    quit->setText("Quit");
    quit->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

    sheet->addChild(quit);
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
 