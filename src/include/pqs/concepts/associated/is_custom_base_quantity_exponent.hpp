#ifndef PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_BASE_QUANTITY_EXPONENT_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{
     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ 
      * @brief is_custom_base_quantity_exp_impl default impl
      **/
        template <typename T>
        inline constexpr bool is_custom_base_quantity_exp_impl = false;
       /** @} */
   }//impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ 
   * @brief is_custom_base_quantity_exp - interface
   **/
   template <typename T>
   inline constexpr bool is_custom_base_quantity_exp 
      = impl::is_custom_base_quantity_exp_impl<std::remove_cvref_t<T> >;
  /** @} */

}

#endif // PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
