#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>

namespace pqs{

   template <unit Unit, dimensionless_quantity ValueType>
   struct basic_quantity;

   template <typename Lhs, typename Rhs>
   struct quantity_plus_semantic;

   /**
    * @brief The default add op where both Lhs and Rhs are in any same measurement system
    * addition of same quantities results in same quantity
    * else returns a basic_quantity with basic unit
    * of simple dimension  and conversion factor of smallest
   */
   template <measurement_system S>
   struct quantity_plus_semantic<S,S>
   {
      template <quantity Lhs, quantity Rhs>
         requires  
         std::is_same_v<get_simple_dimension<Lhs>,get_simple_dimension<Rhs> >
      struct result{
         using type = pqs::basic_quantity <
            pqs::basic_unit<
               S,
               get_simple_dimension<Lhs>,
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

      template <quantity Q>
      struct result<Q,Q>{
         using type = Q;
      };
      
      template <quantity Lhs, quantity Rhs>
         requires  
         std::is_same_v<get_dimension<Lhs>,get_dimension<Rhs> > &&
         provide_quantity_plus<Lhs,Rhs>
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
      provide_quantity_plus<Lhs,Rhs>
   inline constexpr auto operator + ( Lhs const & lhs, Rhs const & rhs)
   {
      return quantity_plus_semantic<
         get_measurement_system<Lhs>,
         get_measurement_system<Rhs>
      >::apply(lhs, rhs);
   }

}

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
