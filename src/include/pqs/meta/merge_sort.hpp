#ifndef PQS_META_MERGE_SORT_HPP_INCLUDED
#define PQS_META_MERGE_SORT_HPP_INCLUDED

#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/type_list.hpp>
#include <pqs/meta/split_list.hpp>
#include <pqs/meta/join_list.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template <typename Lhs_list, typename Rhs_list>
      struct merge_list;

      template <typename Lhs_list, typename Rhs_list>
      struct left_merge_list : push_front<
         typename merge_list<typename pop_front<Lhs_list>::type,Rhs_list>::type,
         typename front<Lhs_list>::type
      >{};

      template <typename Lhs_list, typename Rhs_list>
      struct right_merge_list : push_front<
         typename merge_list<Lhs_list,typename pop_front<Rhs_list>::type>::type,
         typename front<Rhs_list>::type
      >{};

      template <typename... Lhs, typename... Rhs>
      struct merge_list<pqs::meta::type_list<Lhs...>,pqs::meta::type_list<Rhs...> >{

          typedef pqs::meta::type_list<Lhs...> lhs_list;
          typedef pqs::meta::type_list<Rhs...> rhs_list;

          typedef typename front<lhs_list>::type lhs_front;
          typedef typename front<rhs_list>::type rhs_front;

          typedef typename pqs::meta::eval_if_c<
             (lhs_front::value < rhs_front::value),
             left_merge_list<lhs_list,rhs_list>,
             right_merge_list<lhs_list,rhs_list>
          >::type type;
      }; 

      template <typename ...Lhs>
      struct merge_list<pqs::meta::type_list<Lhs...>,pqs::meta::type_list<> > : pqs::meta::type_list<Lhs...>{};

      template <typename... Rhs>
      struct merge_list<pqs::meta::type_list<>,pqs::meta::type_list<Rhs...> > : pqs::meta::type_list<Rhs...>{};

      template <>
      struct merge_list<pqs::meta::type_list<>,pqs::meta::type_list<> > : pqs::meta::type_list<> {};

      template <typename List>
      struct merge_sort_impl{
         typedef pqs::meta::split_list<List> split_type;
         typedef typename split_type::lhs_type_list lhs_split;
         typedef typename split_type::rhs_type_list rhs_split;
         typedef typename merge_sort_impl<lhs_split>::type lhs_merge;
         typedef typename merge_sort_impl<rhs_split>::type rhs_merge;
         typedef typename merge_list<lhs_merge,rhs_merge>::type type;
      };

      template <typename T> 
      struct merge_sort_impl< pqs::meta::type_list<T> > : pqs::meta::type_list<T>{};

      template <> 
      struct merge_sort_impl< pqs::meta::type_list<> > : pqs::meta::type_list<> {};

   }// detail

   template <typename List>
   struct merge_sort {
      typedef typename detail::merge_sort_impl<List>::type type;;
   };
      
}} // pqs::meta

#endif // PQS_META_MERGE_SORT_HPP_INCLUDED
