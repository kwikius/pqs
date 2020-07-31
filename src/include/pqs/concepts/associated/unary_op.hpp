#ifndef PQS_UNARY_OP_HPP_INCLUDED
#define PQS_UNARY_OP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/meta/unary_op_tags.hpp>
#include <pqs/bits/undefined.hpp>

namespace pqs{

   namespace impl{

      template <typename Op, typename T>
      struct unary_op_impl : pqs::undefined{};

   } // impl

   template < typename Op, typename T>
   struct unary_op : impl::unary_op_impl<
      Op,
      std::remove_cvref_t<T>
   >{};

   template < typename Op, typename T>
   using unary_op_t = typename unary_op<Op,T>::type;

}

#endif // PQS_UNARY_OP_HPP_INCLUDED
