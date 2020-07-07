#ifndef PQS_BITS_SCALED_VALUE_HPP_INCLUDED
#define PQS_BITS_SCALED_VALUE_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/concepts/quantity.hpp>
#include <pqs/type_templates/conversion_factor.hpp>

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
         return F::template apply<ValueType>(vR * pqs::conversion_factor_eval<conv_factor>{}());    
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

      constexpr ValueType numeric_value()const { return m_numeric_value;}
      private:
         ValueType m_numeric_value;

  };

}

#endif // PQS_BITS_SCALED_VALUE_HPP_INCLUDED
