#ifndef PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

   struct base_current : pqs::base_quantity_of<pqs::newtonian_universe::current_uuid>{
      typedef base_current type;
   };

   template <int... N>
   struct exp_current;

   template <int N, int D>
   struct exp_current<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_current type; // identity
      typedef type base_exponent_type;
   };

   // for shorter error messages, use an integer exp for the default case
   template <int N>
   struct exp_current<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_current type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_current<N,1> : exp_current<N>{};

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_current<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_current<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::current_uuid,Ratio>
      : exp_current<Ratio::type::num, Ratio::type::den>{};

   }// impl
}

#endif //PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
