#ifndef PQS_SI_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_SI_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/concepts/quantity/plus.hpp>
#include <pqs/si/measurement_system_def.hpp>
#include <pqs/si/unit.hpp>

/**
*  @brief. Implement a custom + semantic for the si measurement system.
*  If the quantities are the same then
      the result is the same as both
 * else if one or both quantities is an si::unit then
 *    get finest grained and convert to basic quantity with si::unit
 * else
      get finest grained 
 *   
*/
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
            ( pqs::si::is_si_unit<lhs_unit >||
              pqs::si::is_si_unit<rhs_unit > ),
            pqs::si::make_si_unit<
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
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;

         return result_type{
            get_numeric_value(result_type{lhs}) + 
            get_numeric_value(result_type{rhs})
         };
      }
   };
}

#endif // PQS_SI_OPERATIONS_PLUS_HPP_INCLUDED
