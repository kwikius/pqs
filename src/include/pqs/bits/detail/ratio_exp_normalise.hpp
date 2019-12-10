#ifndef PQS_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED
#define PQS_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED

#include <pqs/bits/detail/ratio_exp_make_ratio_less_than_10.hpp>
#include <pqs/bits/detail/ratio_exp_make_ratio_greater_equal_1.hpp>

namespace  pqs { namespace detail{

   template <typename Ratio>
   struct ratio_abs{
      typedef typename std::ratio< 
         ((Ratio::num < 0)?-Ratio::num:Ratio::num)
        ,((Ratio::den < 0)?-Ratio::den:Ratio::den)
      >::type type;
   };

   template <typename RatioExp>
   struct ratio_exp_normalise{

      typedef typename pqs::meta::eval_if<
         std::ratio_greater_equal<typename ratio_abs<typename RatioExp::ratio>::type,std::ratio<10,1> >
            ,ratio_exp_make_ratio_less_than_10<
                RatioExp
            >
         ,std::ratio_less<typename ratio_abs<typename RatioExp::ratio>::type,std::ratio<1,1> >
             ,ratio_exp_make_ratio_greater_equal_1<
               RatioExp
             >
         ,RatioExp
      >::type type;
   };

}} // pqs::detail

#endif // PQS_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED
