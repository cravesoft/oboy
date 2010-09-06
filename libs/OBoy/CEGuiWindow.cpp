#include "CEGuiWindow.h"

using namespace Boy;

CEGuiWindow::CEGuiWindow(const std::string& type, const std::string& name) : GuiWindow(), CEGUI::Window(type, name)
{
}

CEGuiWindow::~CEGuiWindow()
{
}

void CEGuiWindow::addChildWindow(GuiWindow* window)
{
  CEGUI::Window::addChildWindow(dynamic_cast<CEGUI::Window*>(window));
}