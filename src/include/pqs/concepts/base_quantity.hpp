#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <pqs/concepts/associated/base_quantity_definition.hpp>
#include <pqs/concepts/associated/get_base_quantity_id.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs::impl{

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
      
} //pqs::impl

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
