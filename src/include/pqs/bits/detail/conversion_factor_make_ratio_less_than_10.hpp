#ifndef QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED
#define QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED

#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

   namespace detail{
      // input RatioExp must always be positive
      template <typename RatioExp>
      struct conversion_factor_abs_make_ratio_less_than_10{
         static_assert(std::ratio_greater<typename RatioExp::ratio,std::ratio<0,1> >::value);
         typedef typename pqs::meta::eval_if<
            std::ratio_less<typename RatioExp::ratio,std::ratio<10> >
            ,RatioExp
            ,conversion_factor_abs_make_ratio_less_than_10<
               conversion_factor<
                  std::ratio_multiply< typename RatioExp::ratio,std::ratio<1,10> >
                  ,RatioExp::exp + 1
               >
            >
         >::type type;            
      };

      // input  RatioExp is non zero
      template <typename RatioExp>
      struct conversion_factor_non_zero_make_ratio_less_than_10{
         static_assert(std::ratio_not_equal<typename RatioExp::ratio,std::ratio<0,1> >::value);

         typedef std::ratio_less< 
            typename RatioExp::ratio,std::ratio<0,1> 
         > is_negative;

         typedef typename pqs::meta::eval_if<
            is_negative
            ,conversion_factor<
               std::ratio_multiply<typename RatioExp::ratio,std::ratio<-1,1> >, 
               RatioExp::exp
             >
            ,RatioExp
         >::type abs_type_in;

         typedef typename conversion_factor_abs_make_ratio_less_than_10<abs_type_in>::type abs_type_out;

         typedef typename pqs::meta::eval_if<
            is_negative
             ,conversion_factor<
                std::ratio_multiply<typename abs_type_out::ratio, std::ratio<-1,1> > 
               ,abs_type_out::exp
            >,
            abs_type_out
         >::type type;
        
      };

      template <typename RatioExp>
      struct conversion_factor_make_ratio_less_than_10{
          // remove zero case
          typedef typename pqs::meta::eval_if<
            std::ratio_equal<typename RatioExp::ratio,std::ratio<0,1> >
            ,conversion_factor< std::ratio<0,1>,0>
            ,conversion_factor_non_zero_make_ratio_less_than_10<RatioExp>
          >::type type;      
      };

   } // detail

} //pqs

#endif // QUAN_DETAIL_CONVERSION_FACTOR_MAKE_RATIO_LESS_THAN_10_HPP_INCLUDED
