#ifndef PQS_META_DETAIL_IS_TYPE_FUNCTION_HPP_INCLUDED
#define PQS_META_DETAIL_IS_TYPE_FUNCTION_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/detail/yes_no_type.hpp>
#include <pqs/meta/detail/has_member_type.hpp>

namespace pqs{ namespace meta{ namespace detail{

   PQS_MACRO_HAS_MEMBER_TYPE(type);

   template <typename T>
   struct is_type_function : 
   std::integral_constant<bool, pqs::meta::detail::has_member_type_type<T>::value>{};

}}}//pqs::meta::impl_detail

#endif



