#ifndef PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 

   /**
   * @addtogroup base_quantity_model
   * @{ **/
   struct base_current : pqs::impl::base_quantity_of<
      pqs::newtonian_universe::current_uuid
   >{
      using type = base_current;
   };
   /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/
   template <int... N> struct exp_current;
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/

   /**
    *  @brief less common rational base_quantity_exponent
    */
   template <int N, int D>
   struct exp_current<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_current type; // identity
      typedef type simple_dimension;
   };
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/

   /**
    *  @brief most common rational base_quantity_exponent
    */
   template <int N>
   struct exp_current<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_current  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_current type; // identity
      typedef type simple_dimension;
   };
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_model
   * @{ **/

   /**
     * Use this form to squash explicit denom when used as a type_function
     */
   template <int N>
   struct exp_current<N,1> : exp_current<N>{};
  /** @} */


   namespace impl{

  /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      /**
       * @brief fulfill base_quantity_exponent requirements
       */
      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_current<N> > = true;
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_current<N,D> > = true;
  /** @} */


  /**
   * @addtogroup base_quantity_exponent_concept_impl
   * @{ **/
      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::current_uuid,Ratio>
      : exp_current<Ratio::type::num, Ratio::type::den>{};
  /** @} */

   }// impl

  /**
   * @addtogroup named_dimension
   * @{ **/
   using abstract_current_t = exp_current<1>;
  /** @} */

  /**
   * @addtogroup named_dimension
   * @{ **/
   inline constexpr auto abstract_current_v = abstract_current_t{};
  /** @} */
   
}

#endif //PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
