#ifndef PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED
#define PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED

/**
*  @brief Forward decl of binary op semantic classes
*/

namespace pqs{ namespace impl {

   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op_semantic;

   template <typename Lhs, typename Op, typename Rhs>
   struct dimensioned_op_semantic;

   template <typename Lhs, typename Op, typename Rhs>
   struct dimensionless_op_semantic;

}} 

#endif // PQS_CONCEPTS_BINARY_OP_SEMANTIC_HPP_INCLUDED
