#ifndef PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_DEFINITION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

/**
 *  @defgroup base_quantity_concept    base_quantity concept
 */
/**
*  @defgroup base_quantity_concept_impl base_quantity concept_impl
*/
/**
 * @defgroup base_quantity_model        base_quantity model_of
 */

   namespace impl{

      /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/

      /**
      * @brief is_base_quantity customisation layer.
      * @param  Any type
      * @return default: false
      */
      template <typename T>
      inline constexpr 
      bool is_base_quantity_impl = false;
      /** @} */
      
   } //impl

  /**
   * @addtogroup base_quantity_concept
   * @{ **/

   /**
   * @brief is_base quantity interface - removes top level cvref for @ref base_quantity_concept_impl layer to see unqualified type
   */
   template <typename T>
   inline constexpr bool is_base_quantity = 
      impl::is_base_quantity_impl< 
         std::remove_cvref_t<T> 
      >;
   /** @} */

  /**
   * @addtogroup base_quantity_concept
   * @{ **/
   
   /**
   *  @brief base_quantity concept definition
   */
   template <typename T>
   concept base_quantity = is_base_quantity<T>;
   /** @} */

} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_DEFINITION_HPP_INCLUDED
