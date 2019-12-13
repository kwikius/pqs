#ifndef PQS_CONCEPTS_META_BOOL_FUN_HPP_INCLUDED
#define PQS_CONCEPTS_META_BOOL_FUN_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>

/*
   is T a valid compile time bool constant?
   implementeation : is there a static 'value' member that is convertible to bool at compile time?
   SFINAE is used to detect the memeber so if it isnt there is not a bool constant, howvere if it is there
   either value --> true or value --> false is ok
*/

namespace pqs{ namespace meta{

   namespace impl{

      template  <typename T, typename Where = void>
      struct is_bool_constant_impl : std::false_type{};

      template <typename T>
      struct is_bool_constant_impl<T,
         typename pqs::where_c<(T::value || !T::value)>::type  
      > : std::true_type{};

   }// impl

   template <typename T>
   struct is_bool_constant : impl::is_bool_constant_impl<T>{};

   #if defined __cpp_concepts

   template <typename T>
   concept bool_constant = is_bool_constant<T>::value;

   #endif

}}//pqs::meta



#endif // PQS_CONCEPTS_META_BOOL_FUN_HPP_INCLUDED
