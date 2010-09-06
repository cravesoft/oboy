#pragma once

namespace Boy
{
  class GuiEventArgs;

  class GuiSlotFunctorBase
  {
  public:

    virtual ~GuiSlotFunctorBase() {};
    virtual bool operator()(const GuiEventArgs& args) = 0;
  };
}