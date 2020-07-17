#ifndef PQS_BINARY_OP_HPP_INCLUDED
#define PQS_BINARY_OP_HPP_INCLUDED

#include <pqs/bits/impl/binary_op_impl.hpp>

namespace pqs{

/**
 * @brief A compile time math op
 * n.b that specialisations with equal_to, less tags
 * will be models of meta::equality_comparable, meta::less_than_comparable
 * if they have a const static "value" member compile time convertible to bool at compile time
 * so best avoid use a bool or int value for compuation unless needed.
 * TODO: make Op a model of binary_operator_tag?
*/
   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op : impl::binary_op_impl<
      std::remove_cvref_t<Lhs>,
      Op,
      std::remove_cvref_t<Rhs>
   >{};

/**
*  @brief member ::value is true if Lhs,Op, Rhs is a valid binary Op
*/
   template <typename Lhs, typename Op, typename Rhs>
   struct is_valid_binary_op : impl::is_valid_binary_op_impl<
      std::remove_cvref_t<Lhs>,
      Op,
      std::remove_cvref_t<Rhs>
   >{};

   /**
    *  shorthand inline typedef for binary_op type_function
    */
   template <typename Lhs, typename Op, typename Rhs>
   using binary_op_t = typename binary_op<Lhs,Op,Rhs>::type;

   /**
    *  shorthand inline bool constant for binary_op value_function
    */
   template <typename Lhs, typename Op, typename Rhs>
   inline constexpr bool binary_op_v = binary_op<Lhs,Op,Rhs>::value;

}

#endif // PQS_BINARY_OP_HPP_INCLUDED
