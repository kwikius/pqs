#ifndef PQS_INSTANCE_BASIC_QUANTITY_DEFINITION_HPP_INCLUDED
#define PQS_INSTANCE_BASIC_QUANTITY_DEFINITION_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/bits/meta/is_narrowing_conversion.hpp>
#if defined PQS_BASIC_QUANTITY_FRIEND_OSTREAM_SUPPORT
#include <pqs/bits/quantity_output.hpp>
#endif

namespace pqs{

   template <unit Unit, dimensionless_quantity ValueType = double>
   struct basic_quantity{

      using unit = Unit;
      using value_type = ValueType;

      constexpr explicit basic_quantity(value_type const & v) : m_scaled_value{v}{}
      constexpr basic_quantity() : m_scaled_value{value_type{}}{}

      constexpr basic_quantity( basic_quantity const & ) = default;
      constexpr basic_quantity& operator =( basic_quantity const & ) = default;

      template <quantity Q>
      constexpr basic_quantity( Q const & q)
         requires
            dimensionally_equivalent<basic_quantity,Q> &&
            same_measurement_system<basic_quantity,Q>  &&
            ! pqs::meta::is_narrowing_conversion<get_numeric_type<Q>,value_type>
      :  m_scaled_value{scaled_value<
            get_conversion_factor<Q>,
            get_numeric_type<Q> 
         >{get_numeric_value(q)}}
      {}

      template <dimensionless_quantity V>
         requires 
            std::is_assignable_v<
               value_type&,
               decltype(std::declval<value_type>() * std::declval<V>())
            >
            && ! meta::is_narrowing_conversion<
               decltype(std::declval<value_type>() * std::declval<V>()),
               value_type
               >
      constexpr 
      basic_quantity & operator *= (V const & v)
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() * v
          );
          return *this;
      }

      template <dimensionless_quantity V>
         requires 
            std::is_assignable_v<
               value_type&,
               decltype(std::declval<value_type>() / std::declval<V>())
            >
            && ! meta::is_narrowing_conversion<
               decltype(std::declval<value_type>() / std::declval<V>()),
               value_type
               >
      constexpr 
      basic_quantity & operator /= (V const & v)
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() / v
          );
          return *this;
      }

      basic_quantity & operator += (basic_quantity const & q)
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() + q.numeric_value()
          );
          return *this;
      }

      basic_quantity & operator -= (basic_quantity const & q)
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() - q.numeric_value()
          );
          return *this;
      }

      constexpr basic_quantity & operator++()
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() + implicit_cast<value_type>(1)
          );
          return *this;
      }

      constexpr basic_quantity & operator--()
      {
          this->m_scaled_value.set_numeric_value( 
              this->numeric_value() - implicit_cast<value_type>(1)
          );
          return *this;
      }

      constexpr value_type numeric_value() const 
      { return m_scaled_value.numeric_value(); }

      // fulfill requirements for basic_quantity to be a model of pqs::quantity
      friend inline constexpr 
      value_type get_numeric_value(basic_quantity const & q)
      {
         return q.numeric_value();
      }
#if defined PQS_BASIC_QUANTITY_FRIEND_OSTREAM_SUPPORT

     friend inline std::ostream & operator << (std::ostream & os, basic_quantity const & q)
     {
        return pqs::output<pqs::default_charset>(os,q);
     }
#endif

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
