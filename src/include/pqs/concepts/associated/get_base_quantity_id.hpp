#ifndef PQS_CONCEPTS_ASSOCIATED_GET_BASE_QUANTITY_ID_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_GET_BASE_QUANTITY_ID_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/associated/base_quantity_definition.hpp>

namespace pqs{

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
      struct get_base_quantity_id_impl : undefined_arg<Qb>{};
      /** @} */
   }

  /**
   * @addtogroup base_quantity_concept
   * @{ **/

   /**
   *  @brief get_base_quantity_id interface - removes top level cvref 
   *  for @ref base_quantity_concept_impl layer to see unqualified type
   */
   template <base_quantity Qb>
   using get_base_quantity_id = 
      typename impl::get_base_quantity_id_impl<
         std::remove_cvref_t<Qb> 
      >::type;
   /** @} */
   
}//pqs

#endif // PQS_CONCEPTS_ASSOCIATED_GET_BASE_QUANTITY_ID_HPP_INCLUDED
