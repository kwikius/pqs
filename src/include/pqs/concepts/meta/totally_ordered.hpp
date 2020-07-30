#ifndef PQS_CONCEPTS_META_TOTALLY_ORDERED_HPP_INCLUDED
#define PQS_CONCEPTS_META_TOTALLY_ORDERED_HPP_INCLUDED

#include <pqs/concepts/meta/less_than_comparable.hpp>
#include <pqs/concepts/meta/equality_comparable.hpp>
#include <pqs/bits/meta/and.hpp>
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

   template <typename TL,typename TR>
   concept totally_ordered = 
      pqs::meta::equality_comparable<TL,TR> && 
      pqs::meta::less_than_comparable<TL,TR>;

}}

#endif // PQS_CONCEPTS_META_TOTALLY_ORDERED_HPP_INCLUDED
