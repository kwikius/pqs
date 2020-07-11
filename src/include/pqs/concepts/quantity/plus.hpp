#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/concepts/binary_op_semantic.hpp>
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
#if 1

   namespace impl{

      template < quantity Lhs, quantity Rhs> 
      struct binary_op_semantic< Lhs, plus, Rhs>{

         using result_dimension = std::conditional_t<
            std::is_same_v< get_dimension<Lhs> , get_dimension<Rhs> >,
            get_dimension<Lhs>,
            get_simple_dimension<Lhs>
         >;

         using result_conversion_factor =  
            meta::min<
               get_conversion_factor<Lhs>,
               get_conversion_factor<Rhs> 
           >;

         using result_unit = 
            basic_unit<
               get_measurement_system<Lhs>,
               result_dimension,
               result_conversion_factor
            >;

         using result_numeric_type = 
            std::remove_cvref_t<
               decltype( 
                  std::declval<
                     binary_op_t<
                        get_numeric_type<Lhs>,
                        plus,
                        get_numeric_type<Rhs>
                     >
                  >() *
                  evaluate<result_conversion_factor>() 
               )
            >;

         using result = 
            basic_quantity<
               result_unit,
               result_numeric_type
            >;

         static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(implicit_cast<result>(lhs)) + 
               get_numeric_value(implicit_cast<result>(rhs))
            };
         }
      };

      // optimise for same quantities
      template <quantity Q> 
      struct binary_op_semantic< Q, plus, Q>{
         static constexpr Q apply( Q const & lhs, Q const & rhs)
         {
            return Q{ get_numeric_value(lhs) + get_numeric_value(rhs) };
         }
      };

   }//impl

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

#else
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

#endif
  
}

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
