#ifndef PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

   // base quantities are required to be model of meta::identity_function 
   struct base_length : pqs::base_quantity_of<pqs::newtonian_universe::length_uuid>{
      typedef base_length type;
   };

   template <int... N>
   struct exp_length;

   template <int N, int D>
   struct exp_length<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_length type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_length<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_length type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_length<N,1> : exp_length<N> {};

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_length<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_length<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::length_uuid,Ratio>
      : exp_length<Ratio::type::num, Ratio::type::den>{};

   }// impl

   template <int N = 1 , int D = 1>
   inline constexpr auto abstract_length = std::conditional_t<
      (D == 1),
      exp_length<N>,
      exp_length<N,D>
   >{};

}

#endif // PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
