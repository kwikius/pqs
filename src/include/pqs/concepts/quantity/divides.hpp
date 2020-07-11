#ifndef PQS_CONCEPTS_QUANTITY_DIVIDES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_DIVIDES_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/concepts/binary_op_semantic.hpp>
#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/meta/min.hpp>

   /**
   * @brief default quantity divide semantic
   */

namespace pqs{

   namespace impl {

      template <quantity Lhs, quantity Rhs> 
      struct dimensioned_op_semantic< Lhs, divides, Rhs>{

         using result_dimension = 
            binary_op_t<
               get_simple_dimension<Lhs>,
               divides,
               get_simple_dimension<Rhs>
            >;
         
         using result_conversion_factor =
            binary_op_t<
               get_conversion_factor<Lhs>,
               divides,
               get_conversion_factor<Rhs> 
            >;

         using result_unit = 
            basic_unit<
               get_measurement_system<Lhs>,
               result_dimension,
               result_conversion_factor
            >;

         using result_numeric_type =
            binary_op_t<
               get_numeric_type<Lhs>,
               divides,
               get_numeric_type<Rhs>
            >;

         using result = 
            pqs::basic_quantity <
               result_unit,
               result_numeric_type
            >;

         static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(lhs) / 
               get_numeric_value(rhs)
            };
         }
      };

      template <quantity Lhs, quantity Rhs> 
      struct dimensionless_op_semantic<Lhs,divides,Rhs>{

         using result_conversion_factor =
            binary_op_t<
               get_conversion_factor<Lhs>,
               divides,
               get_conversion_factor<Rhs> 
            >;

         static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return ( get_numeric_value(lhs) / 
               get_numeric_value(rhs) ) * 
               evaluate<result_conversion_factor >();
         }
      };

      template <quantity Lhs,quantity Rhs>
           requires same_measurement_system<Lhs,Rhs>
      struct binary_op_semantic<Lhs,divides,Rhs> 
      :  std::conditional_t<
            is_dimension<
               binary_op_t<
                  get_simple_dimension<Lhs>, 
                  divides, 
                  get_simple_dimension<Rhs>
               >
            >,
            dimensioned_op_semantic<Lhs,divides,Rhs>,
            dimensionless_op_semantic<Lhs,divides,Rhs>
         >{};
   } // impl
   
   template <quantity Lhs, quantity Rhs>
      requires provide_operator_divides<Lhs,Rhs>
   inline constexpr auto operator / ( Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<
         Lhs,divides, Rhs
      >::apply(lhs, rhs);
   }
} // pqs

#endif // PQS_CONCEPTS_QUANTITY_DIVIDES_QUANTITY_HPP_INCLUDED
