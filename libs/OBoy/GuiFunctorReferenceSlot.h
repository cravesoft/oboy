#pragma once

#include "GuiSlotFunctorBase.h"

namespace Boy
{

  template<typename T> class GuiFunctorReferenceSlot : public GuiSlotFunctorBase
  {
  public:
    GuiFunctorReferenceSlot(T& functor) : d_functor(functor) {}

    virtual bool operator()(const GuiEventArgs& args)
    {
      return d_functor(args);
    }

  private:
    T& d_functor;
  };

}