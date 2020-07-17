#ifndef PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/concepts/associated/binary_op_semantic.hpp>
#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/bits/basic_quantity_fwd.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/types/basic_unit.hpp>
#include <pqs/bits/meta/min.hpp>

   /**
   * @brief default quantity multiplication semantics
   * for dimensioned, dimensionless and scalar ops
   */

namespace pqs{ 
   namespace impl{

      /**
       * @brief default multiplication semantic for when
       * the result is dimensioned
       */ 
      template < quantity Lhs, quantity Rhs> 
      struct dimensioned_out_semantic< Lhs, times, Rhs>{

         using result_dimension = 
            binary_op_t<
               get_simple_dimension<Lhs>,
               times,
               get_simple_dimension<Rhs>
            >;
         
         using result_conversion_factor =
            binary_op_t<
               get_conversion_factor<Lhs>,
               times,
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
               times,
               get_numeric_type<Rhs>
            >;

         using result = 
            pqs::basic_quantity <
               result_unit,
               result_numeric_type
            >;

         static 
         constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(lhs) * 
               get_numeric_value(rhs)
            };
         }
      };

      /**
       * @brief default multiplication semantic for when
       * the result is dimensionless
       */ 

      template <quantity Lhs, quantity Rhs> 
      struct dimensionless_out_semantic<Lhs,times,Rhs>{

         using result_conversion_factor =
            binary_op_t<
               get_conversion_factor<Lhs>,
               times,
               get_conversion_factor<Rhs> 
            >;

         static 
         constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return ( 
               get_numeric_value(lhs) * 
               get_numeric_value(rhs) ) * 
               evaluate< result_conversion_factor >();
         }
      };

      /**
       *  @brief combine the dimensined and dimensionless semantics
       */
      template <quantity Lhs,quantity Rhs>
      struct binary_op_semantic<Lhs,times,Rhs> 
      :  std::conditional_t<
            is_dimension<
               binary_op_t<
                  get_simple_dimension<Lhs>, 
                  times, 
                  get_simple_dimension<Rhs>
               >
            >,
            dimensioned_out_semantic<Lhs,times,Rhs>,
            dimensionless_out_semantic<Lhs,times,Rhs>
        >{};

      /**
       *  @brief multiplication by a scalar q * v
       */
      template <quantity Q, dimensionless_quantity V>
      struct dimensionless_in_semantic<Q, times,V>
      {
         using result = 
            basic_quantity <
               get_unit<Q>,
               binary_op_t<
                  get_numeric_type<Q>, times, V
               >
            >;

         static 
         constexpr auto apply(Q const & q, V const & v)
         {
            return result{get_numeric_value(q) * v};
         }
      };

       /**
       *  @brief multiplication by a scalar v * q
       */

      template <dimensionless_quantity V, quantity Q>
      struct dimensionless_in_semantic<V, times,Q>
      {
         using result = 
            basic_quantity <
               get_unit<Q>,
               binary_op_t<
                  V, times, get_numeric_type<Q>
               >
            >;

         static 
         constexpr auto apply(V const & v, Q const & q)
         {
            return result{v * get_numeric_value(q)};
         }
      };
   }// impl

   /**
    * @brief quantity * dimensionles_quantity
    */

   template <quantity Q, dimensionless_quantity V>
      requires
         provide_operator_times<Q,V>         
   inline constexpr 
   auto operator*( Q const & q, V const & v)
   {
      return impl::dimensionless_in_semantic<
         Q, times, V
      >::apply( q, v);
   }

  /**
    * @brief dimensionles_quantity * quantity
    */

   template <dimensionless_quantity V, quantity Q>
      requires
         provide_operator_times<V,Q>         
   inline constexpr 
   auto operator*( V const & v, Q const & q)
   {
      return impl::dimensionless_in_semantic<
         V, times, Q
      >::apply( v, q);
   }

   /**
    * @brief quantity * quantity
    */
   template <quantity Lhs, quantity Rhs>
      requires
         same_measurement_system<Lhs,Rhs> &&
         provide_operator_times<Lhs,Rhs>         
   inline constexpr 
   auto operator*( Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<
         Lhs, times, Rhs
      >::apply( lhs, rhs);
   }


} // pqs

#endif // PQS_CONCEPTS_QUANTITY_TIMES_QUANTITY_HPP_INCLUDED
