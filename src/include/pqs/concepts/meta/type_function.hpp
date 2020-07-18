#ifndef PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/meta/detail/yes_no_type.hpp>
#include <pqs/bits/meta/detail/has_type_member.hpp>
#include <pqs/bits/meta/strip_cr.hpp>

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

   /**
    *  @brief A type_function has a member ::type
    */
   template <typename T>
   struct is_type_function : impl::is_type_function_impl< std::remove_cvref_t<T> >{};

}} //pqs::meta

#endif  // PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED



