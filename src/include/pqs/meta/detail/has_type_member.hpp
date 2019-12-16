#ifndef PQS_META_DETAIL_HAS_MEMBER_TYPE_HPP_INCLUDED
#define PQS_META_DETAIL_HAS_MEMBER_TYPE_HPP_INCLUDED

/*
  Follows the basic mechanism described in
  C++ Templates the complete guide,
  David Vandevoorde and Nicolia M.Josuttis
   section 15.2.2 determining C++ class types.
*/
#include <pqs/meta/detail/yes_no_type.hpp>
#include <pqs/meta/detail/cat.hpp>

#define PQS_MACRO_HAS_TYPE_MEMBER(name) \
template<typename T> \
struct PQS_MACRO_CAT(has_type_member_,name){\
   template <typename T1>\
   pqs::meta::detail::yes_type static has_type_member_test(typename T1:: name *);\
   template <typename T1>\
   pqs::meta::detail::no_type static has_type_member_test(...);\
   static constexpr bool value = (sizeof(has_type_member_test<T>(0)) == sizeof(pqs::meta::detail::yes_type));\
};

#endif



