#ifndef PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

    struct base_mass : pqs::base_quantity_of<pqs::newtonian_universe::mass_uuid>{
       typedef base_mass type;
    };

   template <int... N>
   struct exp_mass;

   template <int N, int D>
   struct exp_mass<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_mass  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_mass type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_mass<N> : pqs::detail::base_quantity_exp_base_class{
      typedef base_mass  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_mass type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_mass<N,1> : exp_mass<N>{};

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_mass<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_mass<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::mass_uuid,Ratio>
      : exp_mass<Ratio::type::num, Ratio::type::den>{};

   }// impl

#if defined  __cpp_inline_variables

   template <int... N>
   inline constexpr auto exp_mass_v = exp_mass<N...>{};

#endif
}

#endif // PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
