#ifndef PQS_CONCEPTS_META_EQUALITY_COMPARABLE_HPP_INCLUDED
#define PQS_CONCEPTS_META_EQUALITY_COMPARABLE_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/meta/strip_cr.hpp>
#include <pqs/concepts/meta/bool_constant.hpp>
/*
   are 2 meta types equality comparable at compile time?
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
      struct are_equality_comparable_impl : pqs::meta::is_bool_constant<
         pqs::binary_op<TL,pqs::equal_to,TR>
      >{};

   }

   template <typename TL, typename TR>
   struct are_equality_comparable : impl::are_equality_comparable_impl<
      std::remove_cvref_t<TL>,
      std::remove_cvref_t<TR>
   >{};

   template <typename TL,typename TR>
   concept equality_comparable = are_equality_comparable<TL,TR>::value;

}}


#endif // PQS_CONCEPTS_META_EQUALITY_COMPARABLE_HPP_INCLUDED
