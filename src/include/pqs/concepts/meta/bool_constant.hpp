#ifndef PQS_CONCEPTS_META_BOOL_CONSTANT_HPP_INCLUDED
#define PQS_CONCEPTS_META_BOOL_CONSTANT_HPP_INCLUDED

#include <type_traits>

namespace pqs::meta{

   namespace impl{

      template  <typename T>
      struct is_bool_constant_impl : std::false_type{};

      template <typename T>
            requires (static_cast<bool>(T::value) || !static_cast<bool>(T::value) )
      struct is_bool_constant_impl<T
      > : std::true_type{};

   }// impl

/**
 *  @brief Is T a valid compile time bool constant?
 *
 *  implementation : is there a static 'value' member that is convertible to bool at compile time?
 *  SFINAE is used to detect the member so if it isnt there is not a bool constant, however
 *  if it is there  either value --> true or value --> false is ok
*/
   template <typename T>
   struct is_bool_constant : impl::is_bool_constant_impl<T>{};

}//pqs::meta

#endif // PQS_CONCEPTS_META_BOOL_CONSTANT_HPP_INCLUDED
