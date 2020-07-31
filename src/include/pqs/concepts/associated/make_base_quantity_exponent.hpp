#ifndef PQS_CONCEPTS_ASSOCIATED_MAKE_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_MAKE_BASE_QUANTITY_EXPONENT_HPP_INCLUDED

#include <ratio>
#include <type_traits>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/associated/dimensionless.hpp>
#include <pqs/concepts/associated/get_base_quantity_id.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/meta/eval_if.hpp>

namespace pqs{

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
     /**
      * @brief make_base_quantity_exp_impl - customise per UUID
      */
      template <typename UUID,typename Ratio>
      struct make_base_quantity_exp_impl : pqs::undefined_arg<UUID>{};
     /** @} */

   } //impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/

  /**
   * @brief make_base_quantity_exp interface
   */
   template <pqs::base_quantity Qb, typename Ratio>
   struct make_base_quantity_exp : pqs::meta::eval_if<
      std::bool_constant<(Ratio::num == 0)>,
         pqs::dimensionless,
      pqs::impl::make_base_quantity_exp_impl<
         get_base_quantity_id<Qb>, typename Ratio::type
      >
   >{};
   /** @} */

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_MAKE_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
