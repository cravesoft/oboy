#pragma once

namespace Boy
{

  template<typename T> struct GuiFunctorReferenceBinder
  {
    GuiFunctorReferenceBinder(T& functor) : d_functor(functor) {}

    T& d_functor;
  };

}