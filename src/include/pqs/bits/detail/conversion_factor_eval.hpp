#ifndef PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED1
#define PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED1

#include <type_traits>
#include <pqs/math/powerof10.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/meta/narrowest_runtime_type.hpp>
#include <pqs/bits/meta/integer_max.hpp>
#include <pqs/bits/detail/conversion_factor_normalise.hpp>
#include <pqs/bits/detail/to_ll_conversion_factor.hpp>

namespace pqs{

   namespace detail{

      template <typename LLConvFactor>
      struct ll_remove_fractions_of10 :  pqs::meta::eval_if<
         std::integral_constant<bool,( LLConvFactor::multiplier::den %10 == 0)>,
            ll_remove_fractions_of10<
               pqs::detail::ll_conversion_factor< 
                  typename std::ratio_multiply<typename LLConvFactor::multiplier,std::ratio<10> >::type,
                  typename std::ratio_subtract<typename LLConvFactor::exponent,std::ratio<1> >::type
               >
            >,
         LLConvFactor
       >{};

      template <typename LLConvFactor>
      struct ll_eval_integral_conv_factor{

         typedef typename pqs::meta::narrowest_runtime_type<typename LLConvFactor::multiplier>::type mux_rt_type;
         typedef typename pqs::powerof10<typename LLConvFactor::exponent>::type exp_rt_type;
         typedef typename std::common_type<mux_rt_type,exp_rt_type>::type un_promoted_rt_type;
         static_assert(std::is_integral<un_promoted_rt_type>::value,"expected integral conv factor");
         static constexpr int64_t eval_value = (static_cast<int64_t>(LLConvFactor::multiplier::num)/ LLConvFactor::multiplier::den)
               * pqs::powerof10<typename LLConvFactor::exponent>::value;
         static_assert(eval_value > 0,"unexpected negative or zero eval value");
         typedef typename pqs::meta::eval_if<
            std::integral_constant<bool,(eval_value <= pqs::meta::integer_max<int8_t>::value)>,
               pqs::meta::identity<int8_t>,
            std::integral_constant<bool,(eval_value <= pqs::meta::integer_max<int16_t>::value)>,
               pqs::meta::identity<int16_t>,
             std::integral_constant<bool,(eval_value <= pqs::meta::integer_max<int32_t>::value)>,
               pqs::meta::identity<int32_t>,
             pqs::meta::identity<int64_t>
         >::type type;
            
         static constexpr type apply()
         {
            return static_cast<type>(eval_value);
         }
      };

      template <typename LLConvFactor>
      struct ll_eval_float_conv_factor{
         typedef pqs::real_type type;
         static constexpr type apply()
         {
            return (static_cast<type>(LLConvFactor::multiplier::num)/ LLConvFactor::multiplier::den)
               * pqs::powerof10<typename LLConvFactor::exponent>::value;
         }
      };

      template <typename LLConvFactor>
      struct ll_conversion_factor_eval{
      //NB assume convfactor is already normalised?
      typedef typename pqs::detail::ll_conversion_factor_normalise<LLConvFactor>::type normalised_type;
      typedef typename pqs::detail::ll_remove_fractions_of10<normalised_type>::type reduced_type; 

      typedef typename pqs::meta::narrowest_runtime_type<typename reduced_type::multiplier>::type mux_rt_type;
      typedef typename pqs::powerof10<typename reduced_type::exponent>::type exp_rt_type;
      typedef typename std::common_type<mux_rt_type,exp_rt_type>::type un_promoted_rt_type;
      typedef typename pqs::meta::eval_if<
         std::is_integral<un_promoted_rt_type>,
            pqs::meta::identity<detail::ll_eval_integral_conv_factor<reduced_type> >,
         pqs::meta::identity<detail::ll_eval_float_conv_factor<reduced_type> >
      >::type eval_type;
      typedef typename eval_type::type type;

      constexpr type operator()() const
      {
         return eval_type::apply();
      }
      
   };

   }//detail

   template <typename ConversionFactor>
   struct conversion_factor_eval : 
      pqs::detail::ll_conversion_factor_eval<
         typename pqs::detail::to_ll_conversion_factor<ConversionFactor>::type
      >{};

}// pqs

#endif // PQS_BITS_CONVERSION_FACTOR_EVAL_HPP_INCLUDED
