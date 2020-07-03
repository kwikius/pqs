#ifndef PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/type_function.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{ namespace meta{

   namespace impl {

      template <typename T, typename Where = void>
      struct is_identity_function_impl : std::false_type{};

      template <typename T>
      struct is_identity_function_impl <
         T,
         typename pqs::where_<pqs::meta::is_type_function<T> >::type
      > : std::is_same<T,typename T::type>{};

   }

   template <typename T>
   struct is_identity_function : impl::is_identity_function_impl<
      std::remove_cvref_t<T>
   >{};
  
}} //pqs::meta

#endif // PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
