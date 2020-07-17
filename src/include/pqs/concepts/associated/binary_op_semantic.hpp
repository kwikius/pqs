#ifndef PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED
#define PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>

namespace pqs{ namespace impl {

   /**
    * @brief customisable binary op semantic 
    * for +,-,*,/ of 2 quantities
    */
   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op_semantic : undefined{};

   /**
    * @brief default semantic for dimensioned result of Lhs Op Rhs
    */
   template <typename Lhs, typename Op, typename Rhs>
   struct dimensioned_out_semantic : undefined{};

   /**
    * @brief default semantic for dimensionless result of Lhs Op Rhs
    */

   template <typename Lhs, typename Op, typename Rhs>
   struct dimensionless_out_semantic : undefined{};

   /**
    * @brief default semantic for when of Lhs or Rhs is a dimensionless_quantity
    */
   template <typename Lhs, typename Op, typename Rhs>
   struct dimensionless_in_semantic : undefined{};;

}} 

#endif // PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED
