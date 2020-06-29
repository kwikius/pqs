#ifndef PQS_TYPE_TEMPLATES_EXPONENT10_HPP_INCLUDED
#define PQS_TYPE_TEMPLATES_EXPONENT10_HPP_INCLUDED

#include <ratio>
#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/bits/conversion_factor_ops.hpp>

namespace pqs{

   template <int N, int D > 
   struct exponent10 {
      using ratio = typename std::ratio<N,D>::type;
      using type = exponent10;

      template <intmax_t N1, intmax_t D1>
      friend constexpr 
      typename pqs::conversion_factor_normalise<
         pqs::conversion_factor<
            std::ratio<N1,D1>,
            exponent10
         >
      >::type
      operator * ( std::ratio<N1,D1>, exponent10 )
      {
         return {};
      }
   };
}

#endif // PQS_TYPE_TEMPLATES_EXPONENT10_HPP_INCLUDED
