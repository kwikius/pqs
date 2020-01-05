#ifndef PQS_BINARY_OP_HPP_INCLUDED
#define PQS_BINARY_OP_HPP_INCLUDED

//#include <pqs/meta/binary_op_tags.hpp>
//#include <pqs/bits/undefined.hpp>
//#include <pqs/meta/strip_cr.hpp>

#include <pqs/bits/impl/binary_op_impl.hpp>

/*
  n.b that specialisations with equal_to, less tags
  will be models of meta::equality_comparable, meta::less_than_comparable
  if they have a const static "value" member compile time convertible to bool at compile time
  so best avoid use a bool or int value for compuation unless needed.
*/

namespace pqs{

   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op : impl::binary_op_impl<
      typename pqs::meta::strip_cr<Lhs>::type,
         Op,
            typename pqs::meta::strip_cr<Rhs>::type
   >{};

   template <typename Lhs, typename Op, typename Rhs>
   struct is_valid_binary_op : impl::is_valid_binary_op_impl<
      typename pqs::meta::strip_cr<Lhs>::type,
         Op,
            typename pqs::meta::strip_cr<Rhs>::type
   >{};

}

#endif // PQS_BINARY_OP_HPP_INCLUDED
