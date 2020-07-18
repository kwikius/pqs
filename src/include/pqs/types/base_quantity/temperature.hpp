#ifndef PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exponent.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/meta/eval_if.hpp>



namespace pqs{ 
/**
 * @brief implement temperature as a model of base_quantity
*/
    struct base_temperature : pqs::impl::base_quantity_of<pqs::newtonian_universe::temperature_uuid>{
       typedef base_temperature type;
    };

   template <int... N>
   struct exp_temperature;

   template <int N, int D>
   struct exp_temperature<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_temperature type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_temperature<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_temperature type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_temperature<N,1> : exp_temperature<N>{};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_temperature<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_temperature<N,D>  >  = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::temperature_uuid,Ratio>
      : exp_temperature<Ratio::type::num, Ratio::type::den>{};

   }// impl

   template <int N = 1 , int D = 1>
   inline constexpr auto abstract_temperature = std::conditional_t<
      (D == 1),
      exp_temperature<N>,
      exp_temperature<N,D>
   >{};

}

#endif //PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
