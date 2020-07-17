#ifndef PQS_META_JOIN_LIST_HPP_INCLUDED
#define PQS_META_JOIN_LIST_HPP_INCLUDED

#include <pqs/bits/meta/type_list.hpp>

namespace pqs{ namespace meta{

   template <typename Lhs_list, typename Rhs_list>
   struct join_list;

   template <typename ... Lhs, typename ... Rhs>
   struct join_list<pqs::meta::type_list<Lhs...>,pqs::meta::type_list<Rhs...> > {
      typedef pqs::meta::type_list<Lhs...,Rhs...> type;
   };

}}

#endif // PQS_META_JOIN_LIST_HPP_INCLUDED
