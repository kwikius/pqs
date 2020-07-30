#ifndef PQS_CONCEPTS_ASSOCIATED_OF_SAME_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_OF_SAME_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/associated/base_quantity_exponent_definition.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/associated/get_base_quantity.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs{

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename Lhs, typename Rhs>
      inline constexpr auto of_same_base_quantity_impl = pqs::undefined_arg<Lhs,Rhs>{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <base_quantity_exponent Lhs, base_quantity_exponent Rhs>
      inline constexpr bool of_same_base_quantity_impl<
         Lhs,Rhs
      > =  pqs::binary_op_v<
          get_base_quantity<Lhs>,
          pqs::equal_to,
          get_base_quantity<Rhs>
       >;
     /** @} */

   } // impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename Lhs, typename Rhs>
   inline constexpr bool of_same_base_quantity = pqs::impl::of_same_base_quantity_impl<
      std::remove_cvref_t<Lhs>,
      std::remove_cvref_t<Rhs>
   >;
  /** @} */

} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_OF_SAME_BASE_QUANTITY_HPP_INCLUDED
