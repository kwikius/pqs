#ifndef PQS_BITS_SCALED_VALUE_HPP_INCLUDED
#define PQS_BITS_SCALED_VALUE_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/concepts/quantity.hpp>
#include <pqs/bits/conversion_factor.hpp>
#include <pqs/bits/implicit_cast.hpp>

namespace pqs{

  template <typename ValueType, typename ConversionFactor>
  struct scaled_value{

      static_assert(pqs::is_quantity_value_type<ValueType>::value, "invalid value_type for scaled_value");
      static_assert(pqs::meta::is_conversion_factor<ConversionFactor>::value, "invalid conversion factor type for scaled_value");

      typedef ValueType value_type;
      typedef ConversionFactor conversion_factor;

//      template <typename ValueTypeR,typename ConversionFactorR>
//      constexpr 
//      static ValueType scale_from(ValueTypeR const & in);

//      template <typename ValueTypeL, typename ConversionFactorL>
      template <typename ValueTypeR,typename ConversionFactorR, typename F>
      static constexpr 
  //    inline
  //    ValueTypeL
      ValueType
      scale_from (ValueTypeR const & vR, F const & f)
      {
         typedef typename pqs::binary_op<ConversionFactorR,pqs::divides,ConversionFactor>::type conv_factor;
         typedef typename conversion_factor_eval<
            typename std::common_type<ValueType,ValueTypeR>::type,
            conv_factor
         >::type value_type;
         // #########################################################
         // n.b narrowing possible here from ValueType to ValueTypeL
         // use -Wnarrowing , -Wfloat-conversion,-WConversion to flag these conversions
         //##########################################################
         return F::template apply<ValueType>(vR * conversion_factor_eval<value_type, conv_factor>{}());
      }

      template <typename V>
      constexpr 
      explicit
      scaled_value(V const& v, typename pqs::where_<std::is_same<V,value_type> >::type * = nullptr)
      :m_numeric_value{v}{}

      template <typename ValueTypeR,typename ConversionFactorR>
      constexpr 
      scaled_value(scaled_value<ValueTypeR,ConversionFactorR> const & in)
      :m_numeric_value{scale_from<ValueTypeR,ConversionFactorR>(in.numeric_value(),pqs::default_conversion{})}{}

      constexpr ValueType numeric_value()const { return m_numeric_value;}
      private:
         ValueType m_numeric_value;

  };

}

#endif // PQS_BITS_SCALED_VALUE_HPP_INCLUDED
