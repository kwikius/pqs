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
      pqs::normalise<
         pqs::conversion_factor<
            std::ratio<N1,D1>,
            exponent10
         >
      >
      operator ^( std::ratio<N1,D1>, exponent10 )
      {
         return {};
      }

      template <typename Exp>
      struct raise{
         using r1 = typename Exp::ratio;
         using ratio_type = std::ratio_multiply<ratio,r1>;
         using type = pqs::exponent10<
            ratio_type::num,ratio_type::den
         >;
      };

      template <typename Mux, typename Exp>
      friend constexpr 
       pqs::normalise<
         pqs::conversion_factor<
            Mux,
            typename raise<Exp>::type
         >
       > operator ^ ( conversion_factor<Mux,Exp>, exponent10 )
       {
         return {};
       }

   };
}

#endif // PQS_TYPE_TEMPLATES_EXPONENT10_HPP_INCLUDED
