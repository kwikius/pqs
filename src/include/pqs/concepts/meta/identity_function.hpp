#ifndef PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/type_function.hpp>

namespace pqs{ namespace meta{

   namespace impl {

      template <typename T>
      struct is_identity_function_impl : std::false_type{};

      template <typename T>
        requires pqs::meta::is_type_function_v<T>
      struct is_identity_function_impl <
         T 
      > : std::is_same<T,typename T::type>{};

   }

   /**
    * @brief identity function has a member ::type referring to itself
    */
   template <typename T>
   struct is_identity_function : impl::is_identity_function_impl<
      std::remove_cvref_t<T>
   >{};
  
}} //pqs::meta

#endif // PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
