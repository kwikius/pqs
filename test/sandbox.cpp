
#include <type_traits>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/math/to_power.hpp>

namespace {
   struct numeric{};
}

namespace pqs{

   /*
         calc is
   
         ConvFactor::multiplier * 10 ^ convfactor::exponent

        optimisation
         // goal remove exponent if possible
         // goal make mux an integer if possible
         these can be solved by normalisation
         say mux is 1/10 and exp is 1  -> 1
         say mux is 10  and exp is -1 -> 1

         say mux is 12345000  and exp is -3 -> mux:12345, exp:0
          normalisation to 1/10 gives
                mux is  12345/10000  and exp is 4  should go to 12345 exp 0
              rule while mux::denom % 10 ==0 and exp is >=1
               mux: *= 10 and  exp -=1
         // maybe a better form of normalisation? to try to get exp::denom to 1?
       // What is best normal form for a conversion_factor?

       // Options
          1)Make mux between 1 and 10 if exp is not an integer
          2)Make mux an integer if possible. Then If exp is not an integer?
       
   */

   template <typename ConvFactor>
   struct conversion_factor_eval{

      typedef typename std::conditional<
         (ConvFactor::multiplier::den ==1),
            intmax_t,
            double
      >::type mux_type;
      typedef typename std::conditional<
       ( (ConvFactor::exponent::num >= 0) && (ConvFactor::exponent::den ==1) ),
            intmax_t,
            double
      >::type exp_type;

      typedef typename std::common_type<mux_type,exp_type>::type value_type;

      constexpr value_type operator()() const
      {
         return 
            (static_cast<value_type>(ConvFactor::multiplier::num)/ ConvFactor::multiplier::den)
               * pqs::to_power<ConvFactor::exponent::num,ConvFactor::exponent::den>(static_cast<value_type>(10));
      }
      
   };

   template <typename ValueType, typename ConversionFactorL>
   template <typename ConversionFactorR>
   constexpr 
   inline
   typename scaled_value<ValueType,ConversionFactorL>::value_type
   scaled_value<ValueType,ConversionFactorL>::scale_from (typename scaled_value<ValueType,ConversionFactorL>::value_type const & vR)
   {
    //  return ValueType{};
      // v is unscaled value
      // v = vL * kL 
      // v = vR * kR
      // vL * kL = vR * KR
      // vL = vR * kR / kL
      // kL = muxL * 10 ^ ExpL
      // kR = muxR * 10 ^ ExpR
      //  kR/ kL  = (muxR * 10^ExpR)/ (muxL * 10^ExpL)
      //  kR / kL = (muxR / muxL ) * 10^(ExpR- ExpL)
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

   /*
      scale to dimensionless divide (say ) QL/ QR
      vL1 = vL * kL
      vR1 = vR * kR
      v = vL1 / vR1
        = (vL * kL) / ( vR * kR)
        =  vL / vR  * (kL / kR)
      // kL = muxL * 10 ^ ExpL
      // kR = muxR * 10 ^ ExpR
        kL/ kR = (MuxL / MuxR) * 10^( ExpL - ExpR)
      
   */

}

#include <iostream>

void sandbox()
{

   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;
   typedef pqs::conversion_factor<std::ratio<381,125>,std::ratio<-1> > cf_to;



   constexpr pqs::scaled_value<double,cf_from> sv {1.};

   constexpr pqs::scaled_value<double,cf_to> sv1 = sv;

   std::cout << sv1.numeric_value() <<'\n';
   
}