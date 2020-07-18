#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

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

   namespace impl{
     /**
      *  @addtogroup base_quantity_concept_impl
      * @{ */

      /**
      *  @brief default impl of default get_base_quantity_id 
      *  @param Qb model of base_quantity
      *  @return default : undefined ( requires customisation)
      */
      template <typename Qb>
      struct get_base_quantity_id_impl 
      : undefined_arg<Qb>{};
      /** @} */
   }

  /**
   * @addtogroup base_quantity_concept
   * @{ **/

   /**
   *  @brief get_base_quantity_id interface - removes top level cvref for @ref base_quantity_concept_impl layer to see unqualified type
   */
   template <base_quantity Qb>
   using get_base_quantity_id = 
      typename impl::get_base_quantity_id_impl<
         std::remove_cvref_t<Qb> 
      >::type;
   /** @} */
   
   namespace impl{

      /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/

      /**
      *  @brief provide @ref base_quantity_concept totally ordered ,less
      */
      template <base_quantity Lhs,base_quantity Rhs>
      struct binary_op_impl<
         Lhs,less, Rhs
      > : binary_op<
           get_base_quantity_id<Lhs>,
           less, 
           get_base_quantity_id<Rhs>
      >{};
      /** @} */

      /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/

      /**
      *  @brief provide @ref base_quantity_concept totally ordered , equal_to
      */
      template <base_quantity Lhs,base_quantity Rhs>
      struct binary_op_impl<
         Lhs,equal_to, Rhs
      > : binary_op<
         get_base_quantity_id<Lhs>,
         equal_to, 
         get_base_quantity_id<Rhs>
      >{};
      /** @} */
      
   } //impl
} //pqs

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
