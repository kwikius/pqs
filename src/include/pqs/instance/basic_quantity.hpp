#ifndef PQS_INSTANCE_BASIC_QUANTITY_HPP_INCLUDED
#define PQS_INSTANCE_BASIC_QUANTITY_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/scaled_value.hpp>

namespace pqs{

   template <typename Unit, typename ValueType = double>
   struct basic_quantity{

      using unit = Unit;
      using value_type = ValueType;

      constexpr explicit basic_quantity(value_type const & v) : m_scaled_value{v}{}
      constexpr basic_quantity() : m_scaled_value{value_type{}}{}

      constexpr value_type numeric_value() const 
      { return m_scaled_value.numeric_value(); }

    private:
      typedef scaled_value<
         typename unit::conversion_factor,
         value_type
      > scaled_value_type;
      scaled_value_type m_scaled_value;
   };

   // implement requirements for basic_quantity to be a model of quantity

   template <typename Unit, typename ValueType>
   inline constexpr ValueType get_numeric_value(basic_quantity<Unit,ValueType> const & q)
   {
      return q.numeric_value();
   }

   namespace impl{

      // TODO check Unit and ValueType concepts
      template <typename Unit, typename ValueType>
      struct is_quantity_impl<basic_quantity<Unit,ValueType> > : std::true_type{};

      template <typename Unit, typename ValueType>
      struct get_unit_impl<basic_quantity<Unit,ValueType> >{
         using type = Unit;
      };

      template <typename Unit, typename ValueType>
      struct get_numeric_type_impl<basic_quantity<Unit,ValueType> >{
         using type = ValueType;
      };

   }// impl

}

#endif // PQS_INSTANCE_BASIC_QUANTITY_HPP_INCLUDED
