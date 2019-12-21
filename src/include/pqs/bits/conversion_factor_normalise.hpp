#ifndef PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/detail/conversion_factor_make_ratio_less_than_10.hpp>
#include <pqs/bits/detail/conversion_factor_make_ratio_greater_equal_1.hpp>

namespace  pqs { 

   template <typename RatioExp>
   struct conversion_factor_normalise{

      typedef typename pqs::meta::eval_if<
         std::ratio_greater_equal<
            typename pqs::detail::std_ratio_abs<
               typename RatioExp::multiplier
            >::type,
            std::ratio<10,1> 
         >,
            pqs::detail::conversion_factor_make_ratio_less_than_10<
                RatioExp
            >,
         std::ratio_less<typename pqs::detail::std_ratio_abs<typename RatioExp::multiplier>::type,std::ratio<1,1> >
             ,pqs::detail::conversion_factor_make_ratio_greater_equal_1<
               RatioExp
             >,
         RatioExp
      >::type type;
   };

} // pqs

#endif // PQS_DETAIL_CONVERSION_FACTOR_NORMALISE_HPP_INCLUDED
