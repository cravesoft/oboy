#include "WinGui.h"

#include <CEGUI.h>
#include <RendererModules/Direct3D9/CEGUIDirect3D9Renderer.h>
#include <CEGUIDefaultResourceProvider.h>
#include "DXUT.h"

using namespace oboy;

WinGui::WinGui() : Gui()
{
  // create the CEGUI context
  CEGUI::Direct3D9Renderer &renderer = CEGUI::Direct3D9Renderer::create(DXUTGetD3D9Device());
  CEGUI::System::create(renderer);

  // set logging level:
  // logging level is casted to avoid warning compilation
	//	0 : only errors
	//	3 : insane
  CEGUI::Logger::getSingleton().setLoggingLevel((CEGUI::LoggingLevel)3);

  //SetCursor(NULL);
  //DXUTGetD3D9Device()->ShowCursor(false);
  //CEGUI::MouseCursor::getSingleton().hide();
  ShowCursor(false);
}

WinGui::~WinGui()
{
  CEGUI::System::getSingleton().destroy();
}

void WinGui::injectTimePulse(float dt)
{
  CEGUI::System::getSingleton().injectTimePulse(dt);
}

void WinGui::setResourceGroupDirectory(const std::string& resourceGroup, const std::string& directory)
{
  CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
  rp->setResourceGroupDirectory(resourceGroup, directory);
}

void WinGui::setDefaultImagesetResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Imageset::setDefaultResourceGroup(resourceGroup);
}

void WinGui::setDefaultFontResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Font::setDefaultResourceGroup(resourceGroup);
}

void WinGui::setDefaultSchemeResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Scheme::setDefaultResourceGroup(resourceGroup);
}

void WinGui::setDefaultWidgetLookManagerResourceGroup(const std::string& resourceGroup)
{
  CEGUI::WidgetLookManager::setDefaultResourceGroup(resourceGroup);
}

void WinGui::setDefaultWindowManagerResourceGroup(const std::string& resourceGroup)
{
  CEGUI::WindowManager::setDefaultResourceGroup(resourceGroup);
}

void WinGui::setDefaultFont(const std::string& fontName)
{
  CEGUI::System::getSingleton().setDefaultFont(fontName);
}

void WinGui::setDefaultMouseCursor(const std::string& imageset, const std::string& imageName)
{
  CEGUI::System::getSingleton().setDefaultMouseCursor(imageset, imageName);
}

void WinGui::loadSkin(const std::string& fileName)
{
  CEGUI::SchemeManager::getSingleton().create(fileName);
}

void WinGui::loadFont(const std::string& fontName, const float pointSize, const bool antiAliased, const std::string& fontFileName)
{
  CEGUI::FontManager::getSingleton().createFreeTypeFont(fontName, pointSize, antiAliased, fontFileName);
}

void WinGui::draw()
{
  CEGUI::System::getSingleton().renderGUI();
}
#if 0
void WinGui::destroyAllWindows()
{
  CEGUI::WindowManager::getSingleton().destroyAllWindows();
}

GuiWindow* WinGui::createWindow(const std::string& name)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().createWindow(name));
  return window;
}

GuiWindow* WinGui::loadWindowLayout(const std::string& fileName)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout(fileName));
  return window;
}

GuiWindow* WinGui::getWindow(const std::string& name)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().getWindow(name));
  return window;
}

void WinGui::setGUISheet(GuiWindow* window)
{
  CEGUI::System::getSingleton().setGUISheet(dynamic_cast<CEGUI::Window*>(window));
}
#endif