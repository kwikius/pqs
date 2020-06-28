#ifndef PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

    struct base_temperature : pqs::base_quantity_of<pqs::newtonian_universe::temperature_uuid>{
       typedef base_temperature type;
    };

   template <int... N>
   struct exp_temperature;

   template <int N, int D>
   struct exp_temperature<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_temperature type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_temperature<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_temperature type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_temperature<N,1> : exp_temperature<N>{};

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_temperature<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_temperature<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::temperature_uuid,Ratio>
      : exp_temperature<Ratio::type::num, Ratio::type::den>{};

   }// impl

#if defined  __cpp_inline_variables

   template <int N = 1, int D = 1>
   inline constexpr auto abstract_temperature = exp_temperature<N,D>{};

#endif
}

#endif //PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
