#ifndef PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/math/powerof10.hpp>
#include <pqs/bits/binary_op.hpp>

namespace pqs{

   namespace detail{

      template <typename ConvFactor>
      struct remove_fractions_of10 :  pqs::meta::eval_if<
         std::integral_constant<bool,( ConvFactor::multiplier::den %10 == 0)>,
            remove_fractions_of10<
               pqs::conversion_factor< 
                  typename std::ratio_multiply<typename ConvFactor::multiplier,std::ratio<10> >::type,
                  typename std::ratio_subtract<typename ConvFactor::exponent,std::ratio<1> >::type
               >
            >,
         ConvFactor
       >{};

   }//detail

   template <typename ValueType,typename ConvFactor>
   struct conversion_factor_eval{
      //NB assume convfactor is already normalised?
      typedef typename pqs::detail::remove_fractions_of10<ConvFactor>::type reduced_type; 

      typedef typename std::common_type<
         ValueType,
         typename std::conditional<
            (reduced_type::multiplier::den == 1),
               intmax_t,
               double
         >::type,
         typename std::conditional<
          ( (reduced_type::exponent::num >= 0) && (ConvFactor::exponent::den == 1) ),
               intmax_t,
               double
         >::type
      >::type type;

      constexpr type operator()() const
      {
         return 
            (static_cast<type>(reduced_type::multiplier::num)/ reduced_type::multiplier::den)
               * pqs::powerof10<type,typename reduced_type::exponent>::value;
      }
      
   };

}// pqs

#endif // PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED
