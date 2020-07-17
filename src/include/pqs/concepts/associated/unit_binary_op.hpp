#ifndef PQS_BITS_UNIT_BINARY_OP_HPP_INCLUDED
#define PQS_BITS_UNIT_BINARY_OP_HPP_INCLUDED

#include <pqs/concepts/unit.hpp>
#include <pqs/bits/basic_unit_base.hpp>

namespace pqs{

   namespace impl{

      struct unit_binary_op_base : basic_unit_base{};
   }

   /**
    * @brief creates a model of unit fromed from binary op on 
    * two units
   */
   template <unit UnitL, typename Op, unit UnitR>
      requires same_measurement_system<UnitL,UnitR>
            && meta::is_multiplicative_operator<Op>::value
   struct unit_binary_op : impl::unit_binary_op_base{

      using type = unit_binary_op;
      using lhs_unit = UnitL;
      using operation = Op;
      using rhs_unit = UnitR;

      using quantity_system = 
         get_measurement_system<lhs_unit>;

      using dimension = 
         binary_op_t<
            get_dimension<lhs_unit>,
            Op,
            get_dimension<rhs_unit>
         >;
      using conversion_factor = 
         binary_op_t<
            get_conversion_factor<lhs_unit>,
            Op,
            get_conversion_factor<rhs_unit>
         >;       
   };

   template <unit U>
   inline constexpr bool is_unit_binary_op = 
      std::is_base_of_v<
         impl::unit_binary_op_base, 
         std::remove_cvref_t<U> 
      >;

   template <unit Lhs, unit Rhs>
   inline constexpr
   auto operator/( Lhs, Rhs)
   {
      return unit_binary_op<Lhs,divides,Rhs>{};
   }

   template <unit Lhs, unit Rhs>
   inline constexpr
   auto operator*( Lhs, Rhs)
   {
      return unit_binary_op<Lhs,times,Rhs>{};
   }
}

#endif // PQS_BITS_UNIT_BINARY_OP_HPP_INCLUDED
