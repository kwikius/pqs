#ifndef PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_IS_ZERO_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_IS_ZERO_HPP_INCLUDED

#include <ratio>
#include <type_traits>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/associated/dimensionless.hpp>
#include <pqs/concepts/associated/get_exponent.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_definition.hpp>

namespace pqs{

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
      inline constexpr auto base_quantity_exp_is_zero_impl = pqs::undefined_arg<T>{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <base_quantity_exponent T>
      inline constexpr bool base_quantity_exp_is_zero_impl<
         T 
       > = std::ratio_equal_v<get_exponent<T>, std::ratio<0> >;
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <>
      inline constexpr bool base_quantity_exp_is_zero_impl<pqs::dimensionless> = true;
     /** @} */

   } //impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   inline constexpr bool base_quantity_exp_is_zero = impl::base_quantity_exp_is_zero_impl<
      std::remove_cvref_t<T>
   >;
   /** @} */

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_IS_ZERO_HPP_INCLUDED
