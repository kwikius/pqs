#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>

namespace pqs{

   template <unit Unit, dimensionless_quantity ValueType>
   struct basic_quantity;

   template <typename Lhs, typename Rhs>
   struct operator_plus;

   /**
    * @brief The default add op where both Lhs and Rhs are in any same measurement system
    * 
   */
   template <measurement_system S>
   struct operator_plus<S,S>
   {
      template <quantity Lhs, quantity Rhs>
         requires  
         std::is_same_v<get_dimension<Lhs>,get_dimension<Rhs> >
      struct result{
         using type = pqs::basic_quantity <
            pqs::basic_unit<
               S,
               get_dimension<Lhs>,
               std::conditional_t<
                  pqs::binary_op_v<  // choose the smallest unit
                     get_conversion_factor<Lhs>,
                     pqs::less_equal,
                     get_conversion_factor<Rhs>
                  >,
                  get_conversion_factor<Lhs>,
                  get_conversion_factor<Rhs>
               >
            >,
            std::remove_cvref_t<decltype(
               std::declval<get_numeric_type<Lhs> >() + 
               std::declval<get_numeric_type<Rhs> >()
            )>
         >;
      };
// commented out just now only for testing conversions
//      template <quantity Q>
//      struct result<Q,Q>
//      {
//         using type = Q;
//      };
      
      template <quantity Lhs, quantity Rhs>
         requires  
         std::is_same_v<get_dimension<Lhs>,get_dimension<Rhs> > &&
         provide_operator_plus<Lhs,Rhs>
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;

         return result_type{
            get_numeric_value(result_type{lhs}) + 
            get_numeric_value(result_type{rhs})
         };
      }
   };
   
   template <quantity Lhs, quantity Rhs>
      requires  
      std::is_same_v<get_dimension<Lhs>,get_dimension<Rhs> > &&
      provide_operator_plus<Lhs,Rhs>
   inline constexpr auto operator + ( Lhs const & lhs, Rhs const & rhs)
   {
      return operator_plus<
         get_measurement_system<Lhs>,
         get_measurement_system<Rhs>
      >::apply(lhs, rhs);
   }

}

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
