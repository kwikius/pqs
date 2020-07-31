#ifndef PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/concepts/associated/binary_op_semantic.hpp>
#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/concepts/associated/make_unit.hpp>
#include <pqs/bits/meta/min.hpp>

namespace pqs{ 
   namespace impl{

      /**
       * @brief default multiplication semantic for dimensioned result
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
            make_unit<
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
            pqs::make_quantity <
               result_unit,
               result_numeric_type
            >;

         /**
          * @brief implement default dimensioned_out semantic
           */
         static constexpr 
         auto apply( Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(lhs) * 
               get_numeric_value(rhs)
            };
         }
      };

      /**
       * @brief default multiplication semantic for dimensionless result
       */ 
      template <quantity Lhs, quantity Rhs> 
      struct dimensionless_out_semantic<Lhs,times,Rhs>{

         using result_conversion_factor =
            binary_op_t<
               get_conversion_factor<Lhs>,
               times,
               get_conversion_factor<Rhs> 
            >;
         /**
          *  @brief implement default dimensionless_out semantic
          */
         static constexpr 
         auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return ( 
               get_numeric_value(lhs) * 
               get_numeric_value(rhs) ) * 
               evaluate< result_conversion_factor >();
         }
      };

      /**
       *  @brief combine the dimensioned_out and dimensionless_out semantics
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
       *  @brief default semantic for by multiply by dimensionless q * v
       */
      template <quantity Q, dimensionless_quantity V>
      struct dimensionless_in_semantic<Q, times,V>
      {
         using result = 
            make_quantity <
               get_unit<Q>,
               binary_op_t<
                  get_numeric_type<Q>, times, V
               >
            >;

         /**
          * @brief implement default dimensionless_in semantic q * v
          */
         static constexpr 
         auto apply(Q const & q, V const & v)
         {
            return result{get_numeric_value(q) * v};
         }
      };

       /**
       *  @brief default semantic multiplication by dimensionless v * q
       */
      template <dimensionless_quantity V, quantity Q>
      struct dimensionless_in_semantic<V, times,Q>
      {
         using result = 
            make_quantity <
               get_unit<Q>,
               binary_op_t<
                  V, times, get_numeric_type<Q>
               >
            >;

         /**
          * @brief implement default dimensionless_in semantic v * q
          */
         static 
         constexpr auto apply(V const & v, Q const & q)
         {
            return result{v * get_numeric_value(q)};
         }
      };
   }// impl

   /**
    * @brief interface op quantity * dimensionless_quantity
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
    * @brief interface op dimensionless_quantity * quantity
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
    * @brief interface op quantity * quantity
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
