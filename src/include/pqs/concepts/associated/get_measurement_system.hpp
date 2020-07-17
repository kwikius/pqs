#ifndef PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/concepts/measurement_system.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct get_measurement_system_impl : pqs::undefined{};

   }

   template <typename T>
   struct get_measurement_system_legacy 
   : impl::get_measurement_system_impl<
      std::remove_cvref_t<T>
   >{};

   template <typename T>
   using get_measurement_system 
      = typename get_measurement_system_legacy<T>::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED
