#ifndef PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

    struct base_time : pqs::base_quantity_of<pqs::newtonian_universe::time_uuid>{
       typedef base_time type;
    };

   // base_quantity_exps are required to be models of meta::identity_function
   // derive from pqs::detail::base_quantity_exp_base_class
   // to make a model of base_quantity_exp
   // and have member base_type modeliing base_quantity
   // member exponent modelling ratio and representing exponent of base quantity
   template <int N, int D>
   struct expr_time : pqs::detail::base_quantity_exp_base_class {
      typedef base_time  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef expr_time type; // identity
   };

   template <int N>
   struct exp_time : expr_time<N,1> {
      typedef exp_time type; // identity
   };

   namespace impl{

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::time_uuid,Ratio>
      : pqs::meta::eval_if<
         std::integral_constant<bool,(Ratio::den == 1)>,
            exp_time<Ratio::type::num>,
         expr_time<Ratio::type::num, Ratio::type::den>
        >{};

   }// impl

}

#endif // PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
