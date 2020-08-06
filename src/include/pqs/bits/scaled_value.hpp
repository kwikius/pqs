#ifndef PQS_BITS_SCALED_VALUE_HPP_INCLUDED
#define PQS_BITS_SCALED_VALUE_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/types/conversion_factor.hpp>
#include <pqs/bits/implicit_cast.hpp>

namespace pqs{

   template <typename ConversionFactor,pqs::dimensionless_quantity ValueType>
         requires pqs::is_conversion_factor<ConversionFactor>
   struct scaled_value{

      using value_type = ValueType ;
      using conversion_factor = ConversionFactor;

      // F is a function to fix up the value_type
      // see the <pqs/bits/implicit_conversion_functions.hpp> header for some examples
      template <typename ConversionFactorR, pqs::dimensionless_quantity ValueTypeR,typename F>
         requires pqs::is_conversion_factor<ConversionFactorR>
      static constexpr 
      ValueType
      scale_from (ValueTypeR const & vR, F const & f)
      {
         typedef typename pqs::binary_op<ConversionFactorR,pqs::divides,ConversionFactor>::type conv_factor;
         // evaluate<convfactor> returns a double, which needs to be cast to a float if ValutypeR is a float
         // to avoid narrowing issues
         if constexpr (std::is_same_v<ValueTypeR,float> && std::is_same_v<decltype(evaluate<conv_factor>()),double> )
            return F::template apply<ValueType>(vR * static_cast<float>(evaluate<conv_factor>()));
         else
            return F::template apply<ValueType>(vR * evaluate<conv_factor>());    
      }

      template <pqs::dimensionless_quantity V>
      constexpr 
      explicit
      scaled_value(V const& v )
      :m_numeric_value{pqs::default_conversion::template apply<ValueType>(v)}{}

      template <typename ConversionFactorR,pqs::dimensionless_quantity ValueTypeR, typename F>
         requires pqs::is_conversion_factor<ConversionFactorR>
      constexpr 
      explicit
      scaled_value(scaled_value<ConversionFactorR,ValueTypeR> const & in, F const & f)
      :m_numeric_value{scale_from<ConversionFactorR>(in.numeric_value(),f)}{}

      template <typename ConversionFactorR,pqs::dimensionless_quantity ValueTypeR>
         requires pqs::is_conversion_factor<ConversionFactorR>
      constexpr 
      scaled_value(scaled_value<ConversionFactorR,ValueTypeR> const & in)
      :m_numeric_value{scale_from<ConversionFactorR,ValueTypeR>(in.numeric_value(),pqs::default_conversion{})}{}

      void set_numeric_value(value_type const & v){ m_numeric_value = v;}

      constexpr ValueType numeric_value()const { return m_numeric_value;}
      private:
         ValueType m_numeric_value;

  };

}

#endif // PQS_BITS_SCALED_VALUE_HPP_INCLUDED
