#pragma once

#include "GuiEvent.h"
#include <CEGUI.h>

namespace Boy
{
  class CEGuiEvent : public GuiEvent, public CEGUI::Event
	{
	public:

    CEGuiEvent(const std::string& name);
    virtual ~CEGuiEvent();
	};
}

