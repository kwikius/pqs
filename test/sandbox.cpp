
#include <type_traits>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/math/powerof10.hpp>

namespace {
   struct numeric{};
}

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

   template <typename ConvFactor>
   struct conversion_factor_eval{
      typedef typename conversion_factor_normalise<ConvFactor>::type normalised_type; //between 1 and 10
      typedef typename pqs::detail::remove_fractions_of10<normalised_type>::type reduced_type;  // so for example 1234/1000 -> 1234 ; 1/1 -> no change

      typedef typename std::common_type<
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
      >::type value_type;
      constexpr value_type operator()() const
      {
         return 
            (static_cast<value_type>(reduced_type::multiplier::num)/ reduced_type::multiplier::den)
               * pqs::powerof10<value_type,typename reduced_type::exponent>::value;
      }
      
   };

   template <typename ValueType, typename ConversionFactorL>
   template <typename ConversionFactorR>
   constexpr 
   inline
   typename scaled_value<ValueType,ConversionFactorL>::value_type
   scaled_value<ValueType,ConversionFactorL>::scale_from (typename scaled_value<ValueType,ConversionFactorL>::value_type const & vR)
   {
      typedef pqs::conversion_factor<
         typename std::ratio_divide<
            typename ConversionFactorR::multiplier,
            typename ConversionFactorL::multiplier
         >::type,
         typename std::ratio_subtract<
            typename ConversionFactorR::exponent,
            typename ConversionFactorL::exponent
         >::type
       > conv_factor;

       return vR * conversion_factor_eval<conv_factor>{}();
   }

}

#include <iostream>

#if defined PQS_STANDALONE
int main()
#else
void sandbox()
#endif
{

   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  // m
   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<-6> > cf_to;

   pqs::scaled_value<int,cf_from> sv {7};

   pqs::scaled_value<int,cf_to> sv1 = sv;

   std::cout << sv1.numeric_value() <<'\n';
   
}