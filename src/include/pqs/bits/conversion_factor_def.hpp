#ifndef PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
#define PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <type_traits>

namespace pqs{ 

   namespace meta{

      template <typename T> 
      struct is_conversion_factor : std::false_type{};

   }

   // N.B Ratio::type is a std::ratio
   template < typename Ratio, int64_t Exp>
   struct conversion_factor{
      typedef typename Ratio::type ratio;
     // TODO make 0 special case
     // static_assert(ratio::num != 0, "only non-zero ratios values allowed");
      static constexpr int64_t exp = Exp;
      typedef conversion_factor<ratio,exp> type;
   };

   namespace meta{

      template < intmax_t N, intmax_t D, int64_t Exp>
      struct is_conversion_factor<pqs::conversion_factor<std::ratio<N,D>,Exp> > : std::true_type{};

   }

}  // pqs

#endif // PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
