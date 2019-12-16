#ifndef PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/detail/yes_no_type.hpp>
#include <pqs/meta/detail/has_type_member.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <quan/where.hpp>

namespace pqs{ namespace meta{ 

   namespace detail{

      PQS_MACRO_HAS_TYPE_MEMBER(type);

   }//pqs::meta::detail

   namespace impl {

      template <typename T>
      struct is_type_function_impl : std::integral_constant<
         bool, pqs::meta::detail::has_type_member_type<T>::value
      >{};

   }// impl

   template <typename T>
   struct is_type_function : impl::is_type_function_impl<typename pqs::meta::strip_cr<T>::type>{};

}} //pqs::meta

#endif  // PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED



