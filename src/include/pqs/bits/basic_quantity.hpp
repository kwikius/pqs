#ifndef PQS_BASIC_QUANTITY_HPP_INCLUDED
#define PQS_BASIC_QUANTITY_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>

#include <pqs/bits/conversion_factor.hpp>
#include <pqs/bits/scaled_value.hpp>

namespace pqs{

   template <typename Unit, typename ValueType = double>
   struct basic_quantity{

      using unit = Unit;
      using value_type = ValueType;

      constexpr explicit basic_quantity(value_type const & v) : m_scaled_value{v}{}
      constexpr basic_quantity() : m_scaled_value{value_type{}}{}

      constexpr value_type numeric_value() const { return m_scaled_value.numeric_value(); }

    private:
      typedef scaled_value<
         typename unit::conversion_factor,
         value_type
      > scaled_value_type;
      scaled_value_type m_scaled_value;
   };

}

#endif // PQS_BASIC_QUANTITY_HPP_INCLUDED
