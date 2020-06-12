#ifndef PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/base_quantity_exp.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ 

    struct base_intensity : pqs::base_quantity_of<pqs::newtonian_universe::intensity_uuid>{
       typedef base_intensity type;
    };

   template <int... N>
   struct exp_intensity;

   template <int N, int D>
   struct exp_intensity<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_intensity type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_intensity<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_intensity type; // identity
      typedef type base_exponent_type;
   };

   template <int N>
   struct exp_intensity<N,1> : exp_intensity<N>{};

   namespace impl{

      template <int N>
      struct is_base_quantity_exp_impl< pqs::exp_intensity<N>  > : std::true_type{};

      template <int N,int D>
      struct is_base_quantity_exp_impl< pqs::exp_intensity<N,D>  > : std::true_type{};

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::intensity_uuid,Ratio>
      : exp_intensity<Ratio::type::num, Ratio::type::den>{};

   }// impl

#if defined  __cpp_inline_variables

   template <int... N>
   inline constexpr auto exp_intensity_v = exp_intensity<N...>{};

#endif
}

#endif //PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
