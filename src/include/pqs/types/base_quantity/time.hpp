#ifndef PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 

   /**
    * @addtogroup base_quantity_model
    * @{ **/
   /**
    * @brief implement time as a model of base_quantity
   */
   struct base_time : pqs::impl::base_quantity_of<pqs::newtonian_universe::time_uuid>{
      typedef base_time type;
   };
   /** @} */

   template <int... N>
   struct exp_time;

   template <int N, int D>
   struct exp_time<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_time  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_time type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_time<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_time  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_time type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_time<N,1> : exp_time<N>{};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_time<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_time<N,D>  > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::time_uuid,Ratio>
      : exp_time<Ratio::type::num, Ratio::type::den>{};

   }// impl

   using abstract_time_t = exp_time<1>;
   inline constexpr auto abstract_time_v = abstract_time_t{};

}

#endif // PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
