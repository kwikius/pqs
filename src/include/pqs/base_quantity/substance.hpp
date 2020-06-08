#ifndef PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

    struct base_substance : pqs::base_quantity_of<pqs::newtonian_universe::substance_uuid>{
       typedef base_substance type;
    };

   template <int... N>
   struct exp_substance;

   // base_quantity_exps are required to be models of meta::identity_function
   // derive from pqs::detail::base_quantity_exp_base_class
   // to make a model of base_quantity_exp
   // and have member base_type modeliing base_quantity
   // member exponent modelling ratio and representing exponent of base quantity
   template <int N, int D>
   struct exp_substance<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_substance  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_substance type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_substance<N> : exp_substance<N,1> {
      typedef exp_substance type; // identity
      typedef type base_exponent_type;
   };

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_substance<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_substance<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::substance_uuid,Ratio>
      : pqs::meta::eval_if<
         std::integral_constant<bool,(Ratio::den == 1)>,
            exp_substance<Ratio::type::num>,
         exp_substance<Ratio::type::num, Ratio::type::den>
        >{};

   }// impl
}

#endif //PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
