#ifndef PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 

   /**
   * @addtogroup base_quantity_model
   * @{ **/
   struct base_intensity : pqs::impl::base_quantity_of<
      pqs::newtonian_universe::intensity_uuid
   >{
      using type = base_intensity;
   };
   /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/
   template <int... N> struct exp_intensity;
   /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/
   template <int N, int D>
   struct exp_intensity<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_intensity type; // identity
      typedef type simple_dimension;
   };
   /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/
   template <int N>
   struct exp_intensity<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_intensity  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_intensity type; // identity
      typedef type simple_dimension;
   };
   /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/
   template <int N>
   struct exp_intensity<N,1> : exp_intensity<N>{};
   /** @} */

   namespace impl{
 /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_intensity<N> > = true;
   /** @} */

 /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_intensity<N,D> > = true;
   /** @} */

 /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::intensity_uuid,Ratio>
      : exp_intensity<Ratio::type::num, Ratio::type::den>{};
   /** @} */
   }// impl

  /**
   * @addtogroup named_dimension
   * @{ **/
   using abstract_intensity_t = exp_intensity<1>;
   /** @} */

     /**
   * @addtogroup named_dimension
   * @{ **/
   inline constexpr auto abstract_intensity_v = abstract_intensity_t{};
   /** @} */
}

#endif //PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
