#pragma once

#include "GuiEventArgs.h"
#include <CEGUI.h>

namespace Boy
{
  class CEGuiEventArgs : public GuiEventArgs, public CEGUI::EventArgs
	{
	public:

		CEGuiEventArgs();
    virtual ~CEGuiEventArgs();
	};
}

