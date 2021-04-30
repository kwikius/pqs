#ifndef PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 

   /**
    * @addtogroup base_quantity_model
    * @{ */
   /**
    * @brief implement mass as a model of base_quantity
   */
    struct base_mass : pqs::impl::base_quantity_of<pqs::newtonian_universe::mass_uuid>{
       typedef base_mass type;
    };
    /** @} */

   /**
    * @brief implement exp_mass as a model of base_quantity_exponent.
    * Though not a requirement, to shorten error messages, we instantiate 3 different versions:
    * exp_mass<N>  - the most usual option
    * exp_mass<N,D> - the option with a rational power of dimension (not often used but possible).
    * exp_mass<N,1> - the option with a rational power of dimension whose denominator is 1 
    * can be reduced to the integer option in error messages.
    *
    * To allow the specialisations, the default option uses variadic integer template params, but is not defined
   */
   template <int... N>
   struct exp_mass;

   template <int N, int D>
   struct exp_mass<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_mass  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_mass type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_mass<N> : pqs::detail::base_quantity_exp_base_class{
      typedef base_mass  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_mass type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_mass<N,1> : exp_mass<N>{};

   /**
    * @ brief fulfill the requirements to make exp_mass a conforming model of base_quantity_exponent
    */
   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exponent_impl< pqs::exp_mass<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exponent_impl< pqs::exp_mass<N,D>  > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::mass_uuid,Ratio>
      : exp_mass<Ratio::type::num, Ratio::type::den>{};
   }// impl

/**
 * @brief Make a convenient typedef to express mass as a dimension in the standard naming convention
 */
   using abstract_mass_t = exp_mass<1>;

/**
 * @brief Make a convenient constant to express mass as a dimension in the standard naming convention
 */
   inline constexpr auto abstract_mass_v = abstract_mass_t{};

}

#endif // PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
