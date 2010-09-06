#include "GuiSubscriberSlot.h"

using namespace Boy;

GuiSubscriberSlot::GuiSubscriberSlot() : d_functor_impl(0)
{
}


GuiSubscriberSlot::~GuiSubscriberSlot()
{
}

void GuiSubscriberSlot::cleanup()
{
  delete d_functor_impl;
  d_functor_impl = 0;
}
