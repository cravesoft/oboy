#include "CEGuiEvent.h"

using namespace Boy;

CEGuiEvent::CEGuiEvent(const std::string& name) : GuiEvent(name), CEGUI::Event(name)
{
}

CEGuiEvent::~CEGuiEvent()
{
}
