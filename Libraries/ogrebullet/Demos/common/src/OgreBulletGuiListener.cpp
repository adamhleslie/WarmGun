/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "OgreBulletListener.h"
#include "OgreBulletGuiListener.h"

#include <Gui3D/Gui3D.h>
#include <Gui3D/Gui3DPanel.h>
#include <Gui3D/Gui3DPanelColors.h>

using namespace Ogre;

class DemoPanelColors : public Gui3D::PanelColors
{
public:
    DemoPanelColors()
    {
        // General
        transparent = Gorilla::rgb(0, 0, 0, 0);

        // Panel
        panelBackgroundSpriteName = "panelBackground";

        // Button
        buttonInactiveSpriteName = "buttonInactive";
        buttonOveredSpriteName = "buttonOvered";
        buttonNotOveredSpriteName = "buttonNotOvered";
        buttonClickedSpriteName = "buttonClicked";

        buttonBackgroundClickedGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundClickedGradientStart = Gorilla::rgb(255, 255, 255, 200);
        buttonBackgroundClickedGradientEnd = Gorilla::rgb(255, 255, 255, 170);

        buttonBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
        buttonBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 100);

        buttonBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 80);
        buttonBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 50);

        buttonBackgroundInactiveGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundInactiveGradientStart = Gorilla::rgb(255, 255, 255, 15);
        buttonBackgroundInactiveGradientEnd = Gorilla::rgb(255, 255, 255, 5);

        buttonText = Gorilla::rgb(255, 255, 255, 255);
        buttonTextInactive = Gorilla::rgb(255, 255, 255, 70);
        buttonTextSize = 14;

        buttonBorder = Gorilla::rgb(70, 70, 70, 50);
        buttonBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
        buttonBorderInactive = Gorilla::rgb(70, 70, 70, 15);
        buttonBorderSize = 1;

        // Checkbox
        checkboxOveredBackgroundSpriteName = "checkboxOvered";
        checkboxNotOveredBackgroundSpriteName = "checkboxNotOvered";
        checkboxCheckedNotOveredBackgroundSpriteName = "checkboxCheckedNotOvered";
        checkboxCheckedOveredBackgroundSpriteName = "checkboxCheckedOvered";

        // Combobox
        comboboxButtonPreviousOveredSpriteName = "comboboxpreviouselementbuttonovered";
        comboboxButtonPreviousNotOveredSpriteName = "comboboxpreviouselementbuttonnotovered";
        comboboxButtonPreviousInactiveSpriteName = "comboboxpreviouselementbuttoninactive";

        comboboxButtonNextOveredSpriteName = "comboboxnextelementbuttonovered";
        comboboxButtonNextNotOveredSpriteName = "comboboxnextelementbuttonnotovered";
        comboboxButtonNextInactiveSpriteName = "comboboxnextelementbuttoninactive";

        comboboxBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        comboboxBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 0);
        comboboxBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 0);

        comboboxOveredElement = Gorilla::rgb(255, 255, 255, 100);
        comboboxNotOveredElement = Gorilla::rgb(255, 255, 255, 30);
        comboboxSelectedElement = Gorilla::rgb(120, 20, 120, 200);

        comboboxText = Ogre::ColourValue::White;
        comboboxTextSize = 14;

        comboboxBorder = Gorilla::rgb(70, 70, 70, 50);
        comboboxBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
        comboboxBorderSize = 0;

        // InlineSelector
        inlineselectorButtonPreviousOveredSpriteName = "inlineselectorPreviousButtonOvered";
        inlineselectorButtonPreviousNotOveredSpriteName = "inlineselectorPreviousButtonNotOvered";
        inlineselectorButtonPreviousInactiveSpriteName = "inlineselectorPreviousButtonInactive";

        inlineselectorButtonNextOveredSpriteName = "inlineselectorNextButtonOvered";
        inlineselectorButtonNextNotOveredSpriteName = "inlineselectorNextButtonNotOvered";
        inlineselectorButtonNextInactiveSpriteName = "inlineselectorNextButtonInactive";

        inlineselectorBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        inlineselectorBackgroundGradientStart = transparent;
        inlineselectorBackgroundGradientEnd = transparent;

        inlineselectorText = Ogre::ColourValue::White;
        inlineselectorTextSize = 14;

        inlineselectorBorder = transparent;
        inlineselectorBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
        inlineselectorBorderSize = 1;

        // Listbox
        // same value as the combobox
        listboxButtonPreviousOveredSpriteName = comboboxButtonPreviousOveredSpriteName;
        listboxButtonPreviousNotOveredSpriteName = comboboxButtonPreviousNotOveredSpriteName;
        listboxButtonPreviousInactiveSpriteName = comboboxButtonPreviousInactiveSpriteName;

        listboxButtonNextOveredSpriteName = comboboxButtonNextOveredSpriteName;
        listboxButtonNextNotOveredSpriteName = comboboxButtonNextNotOveredSpriteName;
        listboxButtonNextInactiveSpriteName = comboboxButtonNextInactiveSpriteName;

        listboxBackgroundGradientType = comboboxBackgroundGradientType;
        listboxBackgroundGradientStart = comboboxBackgroundGradientStart;
        listboxBackgroundGradientEnd = comboboxBackgroundGradientEnd;

        listboxOveredElement = comboboxOveredElement;
        listboxNotOveredElement = comboboxNotOveredElement;
        listboxOveredSelectedElement = comboboxSelectedElement;
        listboxNotOveredSelectedElement = comboboxSelectedElement + Gorilla::rgb(0, 0, 0, -50);

        listboxText = comboboxText;
        listboxTextSize = 14;

        listboxBorder = comboboxBorder;
        listboxBorderHighlight = comboboxBorderHighlight;
        listboxBorderSize = comboboxBorderSize;

        // Scrollbar
        scrollbarCursorOveredSpriteName = "scrollbarOvered";
        scrollbarCursorNotOveredSpriteName = "scrollbarNotOvered";
        scrollbarCursorSelectedSpriteName = "scrollbarSelected";

        scrollbarBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        scrollbarBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 80);
        scrollbarBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 40);

        scrollbarProgressbarGradientType = Gorilla::Gradient_WestEast;
        scrollbarProgressbarGradientStart = Gorilla::rgb(120, 20, 120, 40);
        scrollbarProgressbarGradientEnd = Gorilla::rgb(120, 20, 120, 80);

        scrollbarText = Ogre::ColourValue::White;
        scrollbarTextSize = 14;

        scrollbarBorder = Gorilla::rgb(70, 70, 70, 50);
        scrollbarBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
        scrollbarCursorBorder =  Gorilla::rgb(120, 20, 120, 150);
        scrollbarBorderSize = 1;
        scrollbarCursorBorderSize = 1;

        // TextZone
        textzoneBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
        textzoneBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
        textzoneBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 90);

        textzoneBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
        textzoneBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 50);
        textzoneBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 20);

        textzoneBackgroundSelectedGradientType = Gorilla::Gradient_NorthSouth;
        textzoneBackgroundSelectedGradientStart = Gorilla::rgb(200, 200, 200, 170);
        textzoneBackgroundSelectedGradientEnd = Gorilla::rgb(200, 200, 200, 140);

        textzoneText = Ogre::ColourValue::White;
        textzoneTextSize = 14;

        textzoneBorder = Gorilla::rgb(70, 70, 70, 50);
        textzoneBorderHighlight = Gorilla::rgb(255, 100, 100, 255);
        textzoneBorderSelected = Gorilla::rgb(255, 200, 200, 200);
        textzoneBorderSize = 1;

        // Caption
        captionBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        captionBackgroundGradientStart = transparent;
        captionBackgroundGradientEnd = transparent;

        captionBorder = transparent;
        captionText = Ogre::ColourValue::White;
        captionTextSize = 14;
        captionBorderSize = 0;

        // ProgressBar
        progressbarBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        progressbarBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 50);
        progressbarBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 70);

        progressbarLoadingBarGradientType = Gorilla::Gradient_NorthSouth;
        progressbarLoadingBarGradientStart = Gorilla::rgb(120, 20, 120, 200);
        progressbarLoadingBarGradientEnd = Gorilla::rgb(120, 20, 120, 150);

        progressbarText = Ogre::ColourValue::White;
        progressbarTextSize = 14;

        progressbarBorder = Gorilla::rgb(70, 70, 70, 50);
        progressbarBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
        progressbarBorderSize = 1;
    }
};

static DemoPanelColors gGuiColors;

// -------------------------------------------------------------------------
OgreBulletGuiListener::OgreBulletGuiListener(OgreBulletListener *listener,
                                             Ogre::Viewport *viewport,
                                             const Ogre::String &atlasName)
    : mGui(NULL),
      mListener(listener),
      mScreen(NULL),
      mMouseLayer(NULL)
{	
    /******************* CREATE Cursor Overlay ***************************/
#if 0
    mMouseOverlay = (Overlay*)OverlayManager::getSingleton().getByName("GuiOverlay");
    if (mMouseOverlay)
    {
        mMousePanel = OverlayManager::getSingleton().getOverlayElement ("GUIMouse");
    }
    else
    {
        mMouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
        mMouseOverlay->setZOrder(600);
        mMousePanel = (Ogre::OverlayElement *)
            OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
        mMousePanel->setMaterialName("OgreBulletDemos/TargetSights");

        TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", "Bullet");
        mMousePanel->setWidth (mouseTex->getWidth() / (float)win->getWidth());
        mMousePanel->setHeight (mouseTex->getHeight() / (float)win->getHeight());

        Ogre::OverlayContainer		*mouseContainer = (Ogre::OverlayContainer*) 
            OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIContainer");
        mMouseOverlay->add2D(mouseContainer);
        mouseContainer->addChild(mMousePanel);
    }

    mMouseOverlay->show(); 
    TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", "Bullet");
    mMouseCursorHalfWidth = (Real(mouseTex->getWidth()) / mWindow->getWidth()) * 0.5;
    mMouseCursorHalfHeight = (Real(mouseTex->getHeight())  / mWindow->getHeight ()) * 0.5;
#endif

    /******************* CREATE GUI ***************************/
    mGui = new Gui3D::Gui3D(&gGuiColors);
    mScreen = mGui->createScreen(viewport, atlasName, "mainScreen");

    mMouseLayer = mScreen->createLayer(4);
    mMouseLayer->createRectangle(viewport->getActualWidth() / 2,
                                 viewport->getActualHeight() / 2,
                                 12, 18);
    mMousePointer->background_image("mousepointer");

//    OverlayContainer* mouseCursor = mGui->createMousePointer(Vector2(32, 32), "bgui.pointer");
//    mouseCursor->hide();

//    mGui->injectMouse(mWindow->getWidth() * 0.5, mWindow->getHeight() * 0.5, false);
}
// -------------------------------------------------------------------------
OgreBulletGuiListener::~OgreBulletGuiListener()
{
    // other buttons  and window managed by BETAGUI will be deleted by BETAGUI himself.
    delete mGui;
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::addBool(Gui3D::Panel *panel,
                                    bool *value,
                                    const Ogre::String &label,
                                    const Ogre::Vector2 &pos)
{
    Gui3D::Checkbox *box = panel->makeCheckbox(pos.x, pos.y, 30, 30);
    panel->makeCaption(pos.x + 40, pos.y,
                       7 * label.size(), 30,
                       label);
    box->setSelecteStateChangedCallback(this, &OgreBulletGuiListener::onBoxCheck);
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::onButtonPress(Gui3D::PanelElement *)
{
}
// -------------------------------------------------------------------------
bool OgreBulletGuiListener::onBoxCheck(Gui3D::PanelElement *)
{
    return true;
}

// -------------------------------------------------------------------------
void OgreBulletGuiListener::setMouseVisiable(bool visiable)
{
    mMouseLayer->setVisible(visiable);
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::setMousePosition(const Ogre::Vector2 &pos)
{
    mMousePointer->position(pos);
//    mMousePanel->setPosition(x - mMouseCursorHalfWidth,
//                             y - mMouseCursorHalfHeight);
}
