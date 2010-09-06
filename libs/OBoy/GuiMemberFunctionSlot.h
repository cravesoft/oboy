#pragma once

#include "GuiSlotFunctorBase.h"

namespace Boy
{

  template<typename T> class GuiMemberFunctionSlot : public GuiSlotFunctorBase
  {
  public:
  
    typedef bool(T::*GuiMemberFunctionType)(const GuiEventArgs&);

    GuiMemberFunctionSlot(GuiMemberFunctionType func, T* obj) : d_function(func), d_object(obj) {}

    virtual bool operator()(const GuiEventArgs& args)
    {
        return (d_object->*d_function)(args);
    }

  private:
    GuiMemberFunctionType d_function;
    T* d_object;
  };

}
