#ifndef PQS_TYPE_FUNCTIONS_GET_CONVERSION_FACTOR_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_CONVERSION_FACTOR_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/types/conversion_factor.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      struct get_conversion_factor_impl : pqs::undefined{};

   }

   template <typename T>
   using get_conversion_factor = 
      impl::get_conversion_factor_impl<
         std::remove_cvref_t<T>
      >::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_CONVERSION_FACTOR_HPP_INCLUDED
