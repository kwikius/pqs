#ifndef PQS_BINARY_OP_HPP_INCLUDED
#define PQS_BINARY_OP_HPP_INCLUDED

#include <pqs/meta/binary_op_tags.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{

   namespace impl{
      template <typename Lhs, typename Op, typename Rhs, typename Where = void>
      struct binary_op_impl : pqs::undefined{};
   }

   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op : impl::binary_op_impl<
      typename pqs::meta::strip_cr<Lhs>::type,
         Op,
            typename pqs::meta::strip_cr<Rhs>::type
   > {};


}


#endif // PQS_BINARY_OP_HPP_INCLUDED
