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
    * @brief The default add op where both Lhs and Rhs are in same measurement system
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
                  pqs::binary_op_v<
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

//      template <quantity Q>
//      struct result<Q,Q>
//      {
//         using type = Q;
//      };
      
      template <quantity Lhs, quantity Rhs>
         requires  
         std::is_same_v<get_dimension<Lhs>,get_dimension<Rhs> > &&
         std::is_same_v<get_measurement_system<Lhs>,S>  &&
         std::is_same_v<get_measurement_system<Rhs>,S>  &&
         provide_operator_plus<Lhs,Rhs>
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;
         result_type const lhs1 = lhs;
         result_type const rhs1 = rhs;
         auto nl = get_numeric_value(lhs1);
         auto nr = get_numeric_value(rhs1);
         return result_type {nl + nr};
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
