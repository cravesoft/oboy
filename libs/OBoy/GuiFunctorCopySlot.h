#pragma once

#include "GuiSlotFunctorBase.h"

namespace Boy
{

  template<typename T> class GuiFunctorCopySlot : public GuiSlotFunctorBase
  {
  public:
    GuiFunctorCopySlot(const T& functor) : d_functor(functor) {}

    virtual bool operator()(const GuiEventArgs& args)
    {
      return d_functor(args);
    }

  private:
    T d_functor;
  };

}