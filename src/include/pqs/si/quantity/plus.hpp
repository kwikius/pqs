#ifndef PQS_SI_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_SI_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/plus.hpp>
#include <pqs/si/measurement_system.hpp>


/**
*  @brief. Implement a custom + semantic for the si measurement system.
*  If the quantities are the same the result is the same, but for different quantities
*  the result is converted to a basic_unit with a multiplier of 1.
*  N.B  just for initial testing. In reality, perhaps a more subtle semantic is required
*/
namespace pqs{

   template <>
   struct quantity_plus_semantic<
      pqs::si_measurement_system,
      pqs::si_measurement_system
   >
   {
      template <quantity Lhs, quantity Rhs>
      struct result{
         using type = pqs::basic_quantity <
            pqs::basic_unit<
               pqs::si_measurement_system,
               get_simple_dimension<Lhs>,
               pqs::si::make_coherent<  // turn the result to a coherent quantity
                  pqs::meta::min<
                     get_conversion_factor<Lhs>,
                     get_conversion_factor<Rhs> 
                  >
               >
            >,
            std::remove_cvref_t<decltype(
               std::declval<get_numeric_type<Lhs> >() + 
               std::declval<get_numeric_type<Rhs> >()
            )>
         >;
      };

      template <quantity Q>
      struct result<Q,Q>
      {
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
