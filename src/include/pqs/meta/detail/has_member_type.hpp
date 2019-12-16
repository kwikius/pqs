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

#define PQS_MACRO_HAS_MEMBER_TYPE(name) \
template<typename T> \
struct PQS_MACRO_CAT(has_member_type_,name){\
   template <typename T1>\
   pqs::meta::detail::yes_type static test(typename T1:: name *);\
   template <typename T1>\
   pqs::meta::detail::no_type static test(...);\
   static const bool value = (sizeof(test<T>(0)) == sizeof(pqs::meta::detail::yes_type));\
};

#endif



