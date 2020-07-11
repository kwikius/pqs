#ifndef PQS_SI_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_SI_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/plus.hpp>
#include <pqs/si/unit.hpp>

/**
 * @brief. Implement a custom + semantic for the 
 * si measurement system.
 *
 * if the quantities are the same then
 *    the result is the same as both
 * else if one or both quantities is a proper si_quantity then
 *    get finest grained and convert it to a proper si quantity
 * else
 *    get finest grained 
 *   
*/
#if 1

namespace pqs { namespace impl{

   
      template < quantity Lhs, quantity Rhs> 
         requires ( pqs::si::is_proper_si_unit<get_unit<Lhs> > ||
              pqs::si::is_proper_si_unit<get_unit<Rhs> > )
         
      struct binary_op_semantic< Lhs, plus, Rhs>{
         //TODO here want to grab same dim if poss
         using result_unit = 
            pqs::si::make_proper_si_unit<
               std::conditional_t<
                  pqs::binary_op_v<
                     get_conversion_factor<Lhs>,
                     pqs::less_equal,
                     get_conversion_factor<Rhs> 
                  >,
                  get_unit<Lhs>,
                  get_unit<Rhs>
               >
            >;

         using lhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Lhs>,
               divides,
               get_conversion_factor<result_unit>
            >;

         using rhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Rhs>,
               divides,
               get_conversion_factor<result_unit>
            >;

         using result_numeric_type =
            std::remove_cvref_t<
               decltype(
                  std::declval< get_numeric_type<Lhs> >()
                     * evaluate< lhs_conversion_factor >() +
                  std::declval< get_numeric_type<Rhs> >()
                     * evaluate< rhs_conversion_factor >()
               )
            >;
         using result = basic_quantity<
            result_unit,
            result_numeric_type
         >;

         static constexpr
         auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(implicit_cast<result>(lhs)) + 
               get_numeric_value(implicit_cast<result>(rhs))
            };
         }
      };

}}// pqs::impl

#else
namespace pqs{

   template <>
   struct quantity_plus_semantic<
      pqs::si_measurement_system,
      pqs::si_measurement_system
   > {
      template <quantity Lhs, quantity Rhs>
      struct result{

         using lhs_unit = pqs::get_unit<Lhs>;
         using rhs_unit = pqs::get_unit<Rhs>;

         using finest_grained_unit = std::conditional_t<
            pqs::binary_op_v<
               get_conversion_factor<Lhs>,
               pqs::less_equal,
               get_conversion_factor<Rhs> 
            >,
            lhs_unit,
            rhs_unit
         >;

         using unit_type = std::conditional_t<
            ( pqs::si::is_proper_si_unit<lhs_unit > ||
              pqs::si::is_proper_si_unit<rhs_unit > ),
            pqs::si::make_proper_si_unit<
               finest_grained_unit
            >,
            finest_grained_unit
         >;
         
         using type = pqs::basic_quantity <
            unit_type,  
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
      static constexpr 
      auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;

         return result_type{
            get_numeric_value(implicit_cast<result_type>(lhs)) + 
            get_numeric_value(implicit_cast<result_type>(rhs))
         };
      }
   };
}
#endif

#endif // PQS_SI_OPERATIONS_PLUS_HPP_INCLUDED
