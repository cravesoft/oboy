#pragma once

#include <string>

namespace Boy
{
	class GuiEvent
	{
	public:

    //typedef Boy::SubscriberSlot Subscriber;

		GuiEvent(const std::string& name) {};
    virtual ~GuiEvent() {};
	};
}

