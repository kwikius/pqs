#ifndef PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/systems/si/unit.hpp>
#include <pqs/bits/named.hpp>

/**
  force unit namespace
*/
namespace pqs::si::force_unit{

  /**
      @todo
      If we have a named dimension
      then it can be used to provide an unprefixed unit
      in a particular measurement system
      similar to the base_unit symbol mechanism
      struct abstract_force : decltype ( abstract_mass_v * abstract_acceleration_v){};
      
       template <typename CharSet>
       get_named_unit_symbol<abstract_force_t
   */

  /**
   * @brief SI named unit demo
   */
   struct N : named_si_unit<"N", abstract_force_t>{};

  /**
   * @brief  prefixed named unit demo : mN
   */
   struct mN : named_si_unit<"mN", abstract_force_t, exponent10<-3> >{};

  /**
   * @brief  prefixed named unit demo : kN
   */
   struct kN : named_si_unit<"kN", abstract_force_t, exponent10<3> >{};

   namespace detail{
      
      /**
        @brief Prefix function for alternative encodings.
         Could presumably be made generic
      */
      template <basic_fixed_string Name, typename Exp, typename CharSet>
      inline auto constexpr 
      prefix_name()
      {
         return  unit_symbol_prefix<Exp::ratio::num,CharSet> + Name;
      }
   }
   /**
    * @brief where the utf8 output differs from ascii an alternative form can be used
    */
    struct uN : normative_unit<abstract_force_t,exponent10<-6> > {
      template <typename CharSet>
      static constexpr auto name = detail::prefix_name<"N",exponent10<-6>,CharSet>();
    };

} // pqs::si::force_unit

#endif // PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
