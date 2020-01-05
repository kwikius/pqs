#ifndef PQS_QUANTITY_HPP_INCLUDED
#define PQS_QUANTITY_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <pqs/bits/conversion_factor.hpp>

namespace pqs{

   /*
      quantity is a model of concrete_quantity
      if
      U is a model of     concrete_quantity_unit
      and V is a model of concrete_quantity_value_type

      other concepts named_concrete_quantity
                     anonymous_concrete_quantity
   */
   template <typename U, typename V = double>
   struct quantity{
      
      constexpr explicit quantity(V const & v) : m_numeric_value{v}{}
      constexpr explicit quantity() : m_numeric_value{V{0}}{}

      constexpr V numeric_value() const { return m_numeric_value; }

      private:
        V m_numeric_value;
   };

}

#endif // PQS_QUANTITY_FWD_HPP_INCLUDED
