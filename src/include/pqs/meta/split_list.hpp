#ifndef PQS_META_SPLIT_LIST_HPP_INCLUDED
#define PQS_META_SPLIT_LIST_HPP_INCLUDED

#include <pqs/meta/type_list.hpp>

namespace pqs { namespace meta{

   template <typename List>
   struct split_list;

   namespace detail{

      template <int I, typename List, typename OtherList>
      struct split_list_impl : split_list_impl<I-1,List, OtherList>{
          
         using base_type = split_list_impl<I-1,List, OtherList> ;
         using rhs_type_list = pop_front_t<typename base_type::rhs_type_list> ;
         using lhs_type_list = push_back_t<
            typename base_type::lhs_type_list,
            front_t<typename base_type::rhs_type_list>
         > ;
      };

      template <typename List, typename OtherList>
      struct split_list_impl<0,List, OtherList>{
          using rhs_type_list = List ;
          using lhs_type_list = type_list<> ;
      };

   }// detail
   
   template <typename ... T>
   struct split_list<pqs::meta::type_list<T...> > : detail::split_list_impl<(sizeof ...(T))/2,type_list<T...>,type_list<> >{};

}}


#endif // PQS_META_SPLIT_LIST_HPP_INCLUDED
