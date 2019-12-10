#ifndef PQS_META_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED
#define PQS_META_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED


#include <pqs/meta/detail/ratio_exp_make_ratio_less_than_10.hpp>
#include <pqs/meta/detail/ratio_exp_make_ratio_greater_than_0_pt_1.hpp>

namespace  pqs { namespace meta{ namespace detail{

   template <typename RatioExp>
   struct ratio_exp_normalise{

      static_assert(std::ratio_greater<typename RatioExp::ratio,std::ratio<0,1> >::value);

      typedef typename eval_if<
         std::ratio_greater_equal<typename RatioExp::ratio,std::ratio<10,1> >
            ,ratio_exp_abs_make_ratio_less_than_10<
                RatioExp
            >
         ,std::ratio_less_equal<typename RatioExp::ratio,std::ratio<1,10> >
             ,ratio_exp_abs_make_ratio_greater_than_0_pt_1<
               RatioExp
             >
         ,RatioExp
      >::type type;
   };

}}} // pqs::meta::detail

#endif // PQS_META_DETAIL_RATIO_EXP_NORMALISE_HPP_INCLUDED
