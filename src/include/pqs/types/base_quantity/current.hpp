#ifndef PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exponent.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/meta/eval_if.hpp>

/**
 * @brief implement current as a model of base_quantity
*/

namespace pqs{ 

   /**
    * @brief current base_quantity definition
   */
   struct base_current : pqs::base_quantity_of<
      pqs::newtonian_universe::current_uuid
   >{
      using type = base_current;
   };

   /**
    * @brief declare the exp_current base_quantity exponent as a variadic template
    * The integer and rational variants are implemented as specialisations
    * to shorten error messages on the usual integer exponents
    * N.B This way of implementing is not essential
    */
   template <int... N>
   struct exp_current;

   //rational specialisation
   template <int N, int D>
   struct exp_current<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_current type; // identity
      typedef type simple_dimension;
   };

   // integer specialisation
   template <int N>
   struct exp_current<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_current type; // identity
      typedef type simple_dimension;
   };

   // squash denom in explicit denom in integer definition
   template <int N>
   struct exp_current<N,1> : exp_current<N>{};

   /**
    * @brief Fulfill base_quantity_exponent requirements
    */
   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_current<N> > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_current<N,D> > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::current_uuid,Ratio>
      : exp_current<Ratio::type::num, Ratio::type::den>{};

   }// impl

   /**
     *  @brief an inline constant of type exp_current for use in runtime expressions
     */
   
   template <int N = 1 , int D = 1>
   inline constexpr auto abstract_current = std::conditional_t<
      (D == 1),
      exp_current<N>,
      exp_current<N,D>
   >{};

}

#endif //PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
