#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/associated/binary_op_semantic.hpp>
#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/basic_quantity_fwd.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/types/basic_unit.hpp>
#include <pqs/bits/meta/min.hpp>
#include <pqs/bits/implicit_cast.hpp>



namespace pqs{

   namespace impl{
   /**
    * @brief The default quantity add semantic
   */
      template < quantity Lhs, quantity Rhs> 
      struct binary_op_semantic< Lhs, plus, Rhs>{

         using result_dimension = std::conditional_t<
            std::is_same_v< 
                  get_dimension<Lhs> , 
                  get_dimension<Rhs> 
               >,
               get_dimension<Lhs>,
               get_simple_dimension<Lhs>
            >;

         using result_conversion_factor =  
            meta::min<
               get_conversion_factor<Lhs>,
               get_conversion_factor<Rhs> 
           >;

         using lhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Lhs>,
               divides,
               result_conversion_factor
            >;

         using rhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Rhs>,
               divides,
               result_conversion_factor
            >;

         using  result_numeric_type =
            std::remove_cvref_t<
               decltype(
                  std::declval< get_numeric_type<Lhs> >()
                     * evaluate< lhs_conversion_factor >() +
                  std::declval< get_numeric_type<Rhs> >()
                     * evaluate< rhs_conversion_factor >()
               )
            >;

         using result_unit = 
            basic_unit<
               get_measurement_system<Lhs>,
               result_dimension,
               result_conversion_factor
            >;

         using result = 
            basic_quantity<
               result_unit,
               result_numeric_type
            >;

         /**
          * @brief Implement the default quantity add semantic
         */
         static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(implicit_cast<result>(lhs)) + 
               get_numeric_value(implicit_cast<result>(rhs))
            };
         }
      };

      /**
        * @brief optimise default add semantic for quantities of exact same type
        */
      template <quantity Q> 
      struct binary_op_semantic< Q, plus, Q>{
         static constexpr Q apply( Q const & lhs, Q const & rhs)
         {
            return Q{ get_numeric_value(lhs) + get_numeric_value(rhs) };
         }
      };

   }//impl

   /**
     * @ brief quantity add operator interface
    */
   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_plus<Lhs,Rhs>
   inline constexpr 
   auto operator+( Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<
         Lhs, plus, Rhs
      >::apply( lhs, rhs);
   }  
} //pqs

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
