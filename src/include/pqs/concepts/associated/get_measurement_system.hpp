#ifndef PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/measurement_system.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct get_measurement_system_impl : pqs::undefined{};
   }

   template <typename T>
   using get_measurement_system = 
      typename impl::get_measurement_system_impl<
         std::remove_cvref_t<T>
      >::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_MEASUREMENT_SYSTEM_HPP_INCLUDED
