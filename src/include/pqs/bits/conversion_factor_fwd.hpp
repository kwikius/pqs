#ifndef PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/exponent10_fwd.hpp>

namespace pqs{

   template <typename Multiplier, typename  Exponent>
      requires pqs::is_ratio<Multiplier> && pqs::is_exponent10<Exponent>
   struct conversion_factor;

   namespace impl{

      template <typename T> 
      struct is_conversion_factor_impl : std::false_type{};
   }

   template  <typename T>
   inline constexpr bool is_conversion_factor = 
      impl::is_conversion_factor_impl< 
         std::remove_cvref_t<T>
      >::value;

}

#endif // PQS_BITS_CONVERSION_FACTOR_FWD_HPP_INCLUDED
