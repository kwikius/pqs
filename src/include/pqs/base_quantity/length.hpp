#ifndef PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

   // base quantities are required to be model of meta::identity_function 
   struct base_length : pqs::base_quantity_of<pqs::newtonian_universe::length_uuid>{
      typedef base_length type;
   };

   // base_quantity_exps are required to be models of meta::identity_function
   // derive from pqs::detail::base_quantity_exp_base_class
   // to make a model of base_quantity_exp
   // and have member base_type modelling base_quantity
   // member exponent modelling ratio and representing exponent of base quantity
   // TODO add unnamed_type to get the type from a named_base_quantity
   template <int N, int D>
   struct expr_length : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef expr_length type; // identity
      typedef type base_exponent_type;
   };

    // TODO add unnamed_type to get the type from a named_base_quantity
   template <int N>
   struct exp_length : expr_length<N,1> {
      typedef exp_length type; // identity
      typedef type base_exponent_type;
   };

   namespace impl{

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::length_uuid,Ratio>
      : pqs::meta::eval_if<
         std::integral_constant<bool,(Ratio::den == 1)>,
            exp_length<Ratio::type::num>,
         expr_length<Ratio::type::num, Ratio::type::den>
        >{};

   }// impl
}

#endif // PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
