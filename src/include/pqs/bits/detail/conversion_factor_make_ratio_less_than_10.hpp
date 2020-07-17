#ifndef QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED
#define QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED

#include <pqs/bits/detail/ll_conversion_factor.hpp>
#include <pqs/bits/meta/eval_if.hpp>

namespace pqs{ 

   namespace detail{
      // input RatioExp must always be positive
      template <typename RatioExp>
      struct ll_conversion_factor_abs_make_ratio_less_than_10{
         static_assert(std::ratio_greater<typename RatioExp::multiplier,std::ratio<0,1> >::value);
         typedef typename pqs::meta::eval_if<
            std::ratio_less<typename RatioExp::multiplier,std::ratio<10> >,
               RatioExp,
            ll_conversion_factor_abs_make_ratio_less_than_10<
               pqs::detail::ll_conversion_factor<
                  std::ratio_multiply< typename RatioExp::multiplier,std::ratio<1,10> >,
                  std::ratio_add<typename RatioExp::exponent,std::ratio<1> >
               >
            >
         >::type type;            
      };

      // input  RatioExp is non zero
      template <typename RatioExp>
      struct ll_conversion_factor_non_zero_make_ratio_less_than_10{
         static_assert(std::ratio_not_equal<typename RatioExp::multiplier,std::ratio<0,1> >::value);

         typedef std::ratio_less< 
            typename RatioExp::multiplier,std::ratio<0,1> 
         > is_negative;

         typedef typename pqs::meta::eval_if<
            is_negative,
               pqs::detail::ll_conversion_factor<
                  std::ratio_multiply<typename RatioExp::multiplier,std::ratio<-1> >, 
                  typename RatioExp::exponent
               >,
            RatioExp
         >::type abs_type_in;

         typedef typename ll_conversion_factor_abs_make_ratio_less_than_10<abs_type_in>::type abs_type_out;

         typedef typename pqs::meta::eval_if<
            is_negative,
            pqs::detail::ll_conversion_factor<
               std::ratio_multiply<typename abs_type_out::multiplier, std::ratio<-1> >, 
               typename abs_type_out::exponent
            >,
            abs_type_out
         >::type type;
        
      };

      template <typename RatioExp>
      struct ll_conversion_factor_make_ratio_less_than_10{
          // remove zero case
          typedef typename pqs::meta::eval_if<
             std::ratio_equal<typename RatioExp::multiplier,std::ratio<0,1> >,
                pqs::detail::ll_conversion_factor< std::ratio<0>,std::ratio<0> >,
             ll_conversion_factor_non_zero_make_ratio_less_than_10<RatioExp>
          >::type type;      
      };

   } // detail

} //pqs

#endif // QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED
