#ifndef PQS_CONCEPTS_META_BOOL_FUN_HPP_INCLUDED
#define PQS_CONCEPTS_META_BOOL_FUN_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>

/*
   is a type a valid compile time bool function?
   is there a static 'value' member that is convertible to bool at compile time?
*/

namespace pqs{ namespace meta{namespace impl{

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
