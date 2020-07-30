#ifndef PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED

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
    * @brief implement temperature as a model of base_quantity
   */
   struct base_temperature : pqs::impl::base_quantity_of<pqs::newtonian_universe::temperature_uuid>{
    typedef base_temperature type;
   };
   /** @} */

   template <int... N>
   struct exp_temperature;

   template <int N, int D>
   struct exp_temperature<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_temperature type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_temperature<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_temperature  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_temperature type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_temperature<N,1> : exp_temperature<N>{};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_temperature<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_temperature<N,D>  >  = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::temperature_uuid,Ratio>
      : exp_temperature<Ratio::type::num, Ratio::type::den>{};

   }// impl

   using abstract_temperature_t = exp_temperature<1>;
   inline constexpr auto abstract_temperature_v = abstract_temperature_t{};

}

#endif //PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
