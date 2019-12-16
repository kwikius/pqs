#ifndef PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED

#include <pqs/meta/strip_cr.hpp>
#include <quan/where.hpp>

namespace pqs{ namespace meta{

   namespace impl {

      namespace detail{ template <typename T> struct quote { typedef typename T::type type;}; }

      template <typename T, typename Where = void>
      struct is_type_function_impl :  std::false_type{};

      template <typename T>
      struct is_type_function_impl<T, typename detail::quote<T>::type > : std::true_type{};
   }

   template <typename T>
   struct is_type_function : impl::is_type_function_impl<typename pqs::meta::strip_cr<T>::type>{};

}} //pqs::meta

#endif // PQS_CONCEPTS_META_TYPE_FUNCTION_HPP_INCLUDED
