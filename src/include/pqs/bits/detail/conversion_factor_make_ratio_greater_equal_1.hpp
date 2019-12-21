#ifndef QUAN_DETAIL_CONVERSION_FACTOR_MAKE_GREATER_EQUAL_1_HPP_INCLUDED
#define QUAN_DETAIL_CONVERSION_FACTOR_MAKE_GREATER_EQUAL_1_HPP_INCLUDED


#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{

   namespace detail{
      // input RatioExp must always be positive
      template <typename RatioExp>
         struct conversion_factor_abs_make_ratio_greater_equal_1{

         static_assert(std::ratio_greater<typename RatioExp::multiplier,std::ratio<0,1> >::value);

         typedef typename meta::eval_if<
            std::ratio_greater_equal<typename RatioExp::multiplier,std::ratio<1> >,
            RatioExp,
            conversion_factor_abs_make_ratio_greater_equal_1<
               conversion_factor< 
                  std::ratio_multiply<typename RatioExp::multiplier,std::ratio<10,1> >,
                  std::ratio_subtract<typename RatioExp::exponent,std::ratio<1> >
               >
            >
         >::type type;            
      };

      // input  RatioExp is non zero
      template <typename RatioExp>
      struct conversion_factor_non_zero_make_ratio_greater_equal_1{

         static_assert(std::ratio_not_equal<typename RatioExp::multiplier,std::ratio<0,1> >::value);

         typedef std::ratio_less< 
            typename RatioExp::multiplier,std::ratio<0,1> 
         > is_negative;

         typedef typename meta::eval_if<
            is_negative,
            conversion_factor<
               std::ratio_multiply<typename RatioExp::multiplier,std::ratio<-1> >, 
               typename RatioExp::exponent
            >,
            RatioExp
         >::type abs_type_in;

         typedef typename conversion_factor_abs_make_ratio_greater_equal_1<abs_type_in>::type abs_type_out;

         typedef typename meta::eval_if<
            is_negative,
            conversion_factor<
               std::ratio_multiply<typename abs_type_out::multiplier, std::ratio<-1> >, 
               typename abs_type_out::exponent
            >,
            abs_type_out
         >::type type;
        
      };

      template <typename RatioExp>
      struct conversion_factor_make_ratio_greater_equal_1{
          // remove zero case
          typedef typename meta::eval_if<
            std::ratio_equal<typename RatioExp::multiplier,std::ratio<0,1> >,
               conversion_factor< std::ratio<0,1>,std::ratio<0> >,
            conversion_factor_non_zero_make_ratio_greater_equal_1<RatioExp>
          >::type type;      
      };

   } // detail

} //pqs

#endif // QUAN_DETAIL_CONVERSION_FACTOR_MAKE_GREATER_EQUAL_1_HPP_INCLUDED
