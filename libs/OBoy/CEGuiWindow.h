#pragma once

#include "GuiWindow.h"
#include <CEGUI.h>

namespace Boy
{
  class CEGuiWindow : public GuiWindow, public CEGUI::Window
	{
	public:

    CEGuiWindow(const std::string& type, const std::string& name);
    virtual ~CEGuiWindow();

    virtual void addChildWindow(GuiWindow* window);
	};
}

