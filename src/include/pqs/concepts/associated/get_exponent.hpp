#ifndef PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined_arg.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      struct get_exponent_impl : pqs::undefined_arg<T>{};
   }

   template <typename T>
   using get_exponent = typename impl::get_exponent_impl<
      typename std::remove_cvref<T>::type
   >::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_EXPONENT_HPP_INCLUDED
