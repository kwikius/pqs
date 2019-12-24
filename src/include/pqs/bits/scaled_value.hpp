#ifndef PQS_BITS_SCALED_VALUE_HPP_INCLUDED
#define PQS_BITS_SCALED_VALUE_HPP_INCLUDED

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

      template <typename ConversionFactorR>
      constexpr 
      static ValueType scale_from(value_type const & in);

      template <typename V>
      constexpr 
      explicit
      scaled_value(V const& v, typename pqs::where_<std::is_same<V,value_type> >::type * = nullptr)
      :m_numeric_value{v}{}

      template <typename ConversionFactorR>
      constexpr 
      scaled_value(scaled_value<ValueType,ConversionFactorR> const & in)
      :m_numeric_value{scale_from<ConversionFactorR>(in.numeric_value())}{}

      constexpr ValueType numeric_value()const { return m_numeric_value;}
      private:
         ValueType m_numeric_value;

  };

}

#endif // PQS_BITS_SCALED_VALUE_HPP_INCLUDED
