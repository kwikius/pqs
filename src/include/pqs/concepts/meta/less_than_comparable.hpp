#ifndef PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED
#define PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/binary_op.hpp>
#include <pqs/concepts/meta/bool_constant.hpp>

/*
   are 2 meta types less_than comparable at compile time?
   The notion is false by default so needs implementation
   for a type.
   The pqs compile time op is achieved by defining a specialisation of
   quan::meta::impl::binary_op_impl<TL,equal_to,TR>
   which rhas a true false value for those types you want to
   model
*/
namespace pqs{ namespace meta{

   namespace impl {

      template <typename TL, typename TR, typename Where = void>
      struct are_less_than_comparable_impl : pqs::meta::is_bool_constant<
         pqs::binary_op<TL,pqs::less,TR>
      >{};

   }

   template <typename TL, typename TR>
   struct are_less_than_comparable : impl::are_less_than_comparable_impl<
      typename pqs::meta::strip_cr<TL>::type,
      typename pqs::meta::strip_cr<TR>::type
   >{};

   template <typename TL,typename TR>
   concept less_than_comparable = are_less_than_comparable<TL,TR>::value;


}}


#endif // PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED
