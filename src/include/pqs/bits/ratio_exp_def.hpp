#ifndef PQS_RATIO_EXP_DEF_HPP_INCLUDED
#define PQS_RATIO_EXP_DEF_HPP_INCLUDED

#include <ratio>
#include <type_traits>

namespace pqs{ 

   namespace meta{

      template <typename T> struct is_ratio_exp : std::false_type{};

   }

   // N.B Ratio::type is a std::ratio
   template < typename Ratio, int64_t Exp>
   struct ratio_exp{
      typedef typename Ratio::type ratio;
      static_assert(ratio::num != 0, "only non-zero ratios values allowed");
      static constexpr int64_t exp = Exp;
      typedef ratio_exp<ratio,exp> type;
   };

   namespace meta{

      template < intmax_t N, intmax_t D, int64_t Exp>
      struct is_ratio_exp<pqs::ratio_exp<std::ratio<N,D>,Exp> > : std::true_type{};

   }

}  // pqs

#endif // PQS_RATIO_EXP_DEF_HPP_INCLUDED
