#pragma once

#include "GuiFunctorCopySlot.h"
#include "GuiFunctorReferenceSlot.h"
#include "GuiFunctorPointerSlot.h"
#include "GuiMemberFunctionSlot.h"
#include "GuiFunctorReferenceBinder.h"

namespace Boy
{
  class GuiSubscriberSlot
	{
	public:

		GuiSubscriberSlot();
    ~GuiSubscriberSlot();

    bool operator() (const GuiEventArgs& args) const
    {
        return (*d_functor_impl)(args);
    }

    bool connected() const
    {
        return d_functor_impl != 0;
    }

    void cleanup();

    template<typename T>
    GuiSubscriberSlot(bool (T::*function)(const GuiEventArgs&), T* obj) :
        d_functor_impl(new GuiMemberFunctionSlot<T>(function, obj))
    {}

    template<typename T>
    GuiSubscriberSlot(const GuiFunctorReferenceBinder<T>& binder) :
        d_functor_impl(new GuiFunctorReferenceSlot<T>(binder.d_functor))
    {}

    template<typename T>
    GuiSubscriberSlot(const T& functor) :
        d_functor_impl(new GuiFunctorCopySlot<T>(functor))
    {}

    template<typename T>
    GuiSubscriberSlot(T* functor) :
        d_functor_impl(new GuiFunctorPointerSlot<T>(functor))
    {}

  private:

    GuiSlotFunctorBase* d_functor_impl;
	};
}

