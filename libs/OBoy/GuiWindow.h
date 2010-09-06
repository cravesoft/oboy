#pragma once

#include <string>
#include <CEGUI.h>

namespace Boy
{
	class GuiWindow
	{
	public:

		GuiWindow() {};
    virtual ~GuiWindow() {};

    virtual void setEnabled(bool enabled) = 0;
		virtual bool isEnabled() = 0;

    virtual void subscribeEvent(const CEGUI::String& name, CEGUI::Event::Subscriber subscriber) = 0;
    virtual void setProperty(const std::string& name, const std::string& value) = 0; 
    virtual void addChildWindow(GuiWindow* window) = 0;
    virtual void setWantsMultiClickEvents(bool setting) = 0;

	};
}
