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

 // base_quantity_exps are required to be models of meta::identity_function
   // Derive from pqs::detail::base_quantity_exp_base_class
   // to make a model of base_quantity_exp.
   // Must have member base_type modelling base_quantity.
   // Must have member exponent modelling ratio and representing exponent of base quantity.
   template <int N, int D>
   struct expr_current : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef expr_current type; // identity
      typedef type base_exponent_type;
   };

   // for shorter error messages, use an integer exp for the default case
   template <int N>
   struct exp_current : expr_current<N,1> {
      typedef exp_current type; // identity
      typedef type base_exponent_type;
   };

   namespace impl{

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::current_uuid,Ratio>
      : pqs::meta::eval_if<
         std::integral_constant<bool,(Ratio::den == 1)>,
            exp_current<Ratio::type::num>,
         expr_current<Ratio::type::num, Ratio::type::den>
        >{};

   }// impl
}

#endif //PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
