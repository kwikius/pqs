#ifndef PQS_META_MIN_HPP_INCLUDED
#define PQS_META_MIN_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs { namespace meta{

   namespace impl{
      template <typename Lhs, typename Rhs>
      struct min_impl : std::conditional<
         pqs::binary_op_v<Lhs,pqs::less_equal,Rhs>,
         Lhs,
         Rhs
      >{};
   }

   template <typename Lhs, typename Rhs>
   using min = typename impl::min_impl<Lhs,Rhs>::type;

}}

#endif // PQS_META_MIN_HPP_INCLUDED
