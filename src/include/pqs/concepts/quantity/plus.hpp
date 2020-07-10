#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/meta/min.hpp>
#include <pqs/bits/implicit_cast.hpp>

   /**
    * @brief The default add op where both Lhs and Rhs 
    * are in any same measurement system.
    * Addition of same quantities results in same quantity
    * else returns a basic_quantity with basic unit
    * of simple dimension  and conversion factor of smallest
    * N.B. These are low level operations. We rely on the 
    * top level operator + for requirements checking
   */

namespace pqs{

   template <typename LhsMS, typename RhsMS>
   struct quantity_plus_semantic;

   template <measurement_system S>
   struct quantity_plus_semantic<S,S>
   {
      template <quantity Lhs, quantity Rhs>
      struct result{
         using type = basic_quantity <
            basic_unit<
               S,
               get_simple_dimension<Lhs>,
               meta::min<
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
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(implicit_cast<result_type>(lhs)) + 
            get_numeric_value(implicit_cast<result_type>(rhs))
         };
      }
   };
   
   template <quantity Lhs, quantity Rhs>
      requires  
      dimensionally_equivalent<Lhs,Rhs> &&
      provide_operator_plus<Lhs,Rhs>
   inline constexpr 
   auto operator + ( Lhs const & lhs, Rhs const & rhs)
   {
      return quantity_plus_semantic<
         get_measurement_system<Lhs>,
         get_measurement_system<Rhs>
      >::apply(lhs, rhs);
   }
}

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
