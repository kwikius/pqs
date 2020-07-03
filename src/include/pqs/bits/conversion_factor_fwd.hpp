#ifndef PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/type_templates/exponent10_fwd.hpp>
#include <pqs/type_functions/get_exponent.hpp>

namespace pqs{

   template <typename Multiplier, typename  Exponent>
   struct conversion_factor;

   namespace impl{

      template <typename T, typename Where = void> 
      struct is_conversion_factor_impl : std::false_type{};
   }

   template <typename T>
   struct is_conversion_factor_legacy : impl::is_conversion_factor_impl< 
      std::remove_cvref_t<T>
   >{};

   template  <typename T>
   inline constexpr bool is_conversion_factor = is_conversion_factor_legacy<T>::value;

}

#endif // PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
