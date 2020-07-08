#ifndef PQS_INSTANCE_BASIC_QUANTITY_DEFINITION_HPP_INCLUDED
#define PQS_INSTANCE_BASIC_QUANTITY_DEFINITION_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/meta/is_narrowing_conversion.hpp>

namespace pqs{

   template <unit Unit, dimensionless_quantity ValueType = double>
   struct basic_quantity{

      using unit = Unit;
      using value_type = ValueType;

      constexpr explicit basic_quantity(value_type const & v) : m_scaled_value{v}{}
      constexpr basic_quantity() : m_scaled_value{value_type{}}{}

      constexpr basic_quantity( basic_quantity const & ) = default;

      template <quantity Q>
      constexpr basic_quantity( Q const & q)
         requires
            std::is_same_v< get_dimension<unit>,get_dimension<Q> > &&
            std::is_same_v<get_measurement_system<unit>,get_measurement_system<Q> > &&
            ! pqs::meta::is_narrowing_conversion<get_numeric_type<Q>,value_type>
      :  m_scaled_value{scaled_value<
            get_conversion_factor<Q>,
            get_numeric_type<Q> 
         >{get_numeric_value(q)}}
      {}

      constexpr value_type numeric_value() const 
      { return m_scaled_value.numeric_value(); }

      // fulfill requirements for basic_quantity to be a model of pqs::quantity
      friend inline constexpr 
      value_type get_numeric_value(basic_quantity const & q)
      {
         return q.numeric_value();
      }

    private:
      using scaled_value_type = scaled_value<
         get_conversion_factor<unit>,
         value_type
      > ;
      scaled_value_type m_scaled_value;
   };


   // fulfill requirements for basic_quantity to be a model of pqs::quantity
   namespace impl{

      // TODO check Unit and ValueType concepts
      template <typename Unit, typename ValueType>
      struct is_quantity_impl<
         basic_quantity<Unit,ValueType> 
      > : std::true_type{};

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
