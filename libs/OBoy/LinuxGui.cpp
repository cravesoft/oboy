#include "LinuxGui.h"

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIDefaultResourceProvider.h>

using namespace oboy;

LinuxGui::LinuxGui() : Gui()
{
  // create the CEGUI context
  CEGUI::OpenGLRenderer &renderer = CEGUI::OpenGLRenderer::create();
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

LinuxGui::~LinuxGui()
{
  CEGUI::System::getSingleton().destroy();
}

void LinuxGui::injectTimePulse(float dt)
{
  CEGUI::System::getSingleton().injectTimePulse(dt);
}

void LinuxGui::setResourceGroupDirectory(const std::string& resourceGroup, const std::string& directory)
{
  CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
  rp->setResourceGroupDirectory(resourceGroup, directory);
}

void LinuxGui::setDefaultImagesetResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Imageset::setDefaultResourceGroup(resourceGroup);
}

void LinuxGui::setDefaultFontResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Font::setDefaultResourceGroup(resourceGroup);
}

void LinuxGui::setDefaultSchemeResourceGroup(const std::string& resourceGroup)
{
  CEGUI::Scheme::setDefaultResourceGroup(resourceGroup);
}

void LinuxGui::setDefaultWidgetLookManagerResourceGroup(const std::string& resourceGroup)
{
  CEGUI::WidgetLookManager::setDefaultResourceGroup(resourceGroup);
}

void LinuxGui::setDefaultWindowManagerResourceGroup(const std::string& resourceGroup)
{
  CEGUI::WindowManager::setDefaultResourceGroup(resourceGroup);
}

void LinuxGui::setDefaultFont(const std::string& fontName)
{
  CEGUI::System::getSingleton().setDefaultFont(fontName);
}

void LinuxGui::setDefaultMouseCursor(const std::string& imageset, const std::string& imageName)
{
  CEGUI::System::getSingleton().setDefaultMouseCursor(imageset, imageName);
}

void LinuxGui::loadSkin(const std::string& fileName)
{
  CEGUI::SchemeManager::getSingleton().create(fileName);
}

void LinuxGui::loadFont(const std::string& fontName, const float pointSize, const bool antiAliased, const std::string& fontFileName)
{
  CEGUI::FontManager::getSingleton().createFreeTypeFont(fontName, pointSize, antiAliased, fontFileName);
}

void LinuxGui::draw()
{
  CEGUI::System::getSingleton().renderGUI();
}

/*void LinuxGui::destroyAllWindows()
{
  CEGUI::WindowManager::getSingleton().destroyAllWindows();
}

GuiWindow* LinuxGui::createWindow(const std::string& name)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().createWindow(name));
  return window;
}

GuiWindow* LinuxGui::loadWindowLayout(const std::string& fileName)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout(fileName));
  return window;
}

GuiWindow* LinuxGui::getWindow(const std::string& name)
{
  CEGuiWindow* window = dynamic_cast<CEGuiWindow*>(CEGUI::WindowManager::getSingleton().getWindow(name));
  return window;
}

void LinuxGui::setGUISheet(GuiWindow* window)
{
  CEGUI::System::getSingleton().setGUISheet(dynamic_cast<CEGUI::Window*>(window));
}*/