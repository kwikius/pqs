#ifndef PQS_BITS_EVALUATE_CONVERSION_FACTOR_HPP_INCLUDED
#define PQS_BITS_EVALUATE_CONVERSION_FACTOR_HPP_INCLUDED

#include <pqs/bits/conversion_factor_fwd.hpp>
#include <pqs/bits/detail/conversion_factor_eval.hpp>
#include <pqs/bits/conversion_factor_def.hpp>

namespace pqs{

   template <typename ConversionFactor>
      requires pqs::is_conversion_factor<ConversionFactor>
   inline constexpr
   auto evaluate()
   {
      return conversion_factor_eval<ConversionFactor>{}();
   }

}


#endif // PQS_BITS_EVALUATE_CONVERSION_FACTOR_HPP_INCLUDED
