#ifndef PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_DEFINITION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

/**
 *  @defgroup base_quantity_exponent_concept    base_quantity_exponent concept
 */

/**
 *  @defgroup base_quantity_exponent_concept_impl    base_quantity_exponent concept_impl
 */

/**
 *  @defgroup base_quantity_exponent_model    base_quantity_exponent model_of
 */

/**
 *  @defgroup named_dimension  named dimension
 */

   namespace impl{
      
     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
      inline constexpr bool is_base_quantity_exp_impl = false;
     /** @} */

   } // impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   inline constexpr bool is_base_quantity_exponent = 
      impl::is_base_quantity_exp_impl< std::remove_cvref_t<T> >;
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   concept base_quantity_exponent = 
      impl::is_base_quantity_exp_impl< std::remove_cvref_t<T> >;
  /** @} */

} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_DEFINITION_HPP_INCLUDED
