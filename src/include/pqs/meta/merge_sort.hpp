#ifndef PQS_META_MERGE_SORT_HPP_INCLUDED
#define PQS_META_MERGE_SORT_HPP_INCLUDED

#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/type_list.hpp>
#include <pqs/meta/split_list.hpp>
#include <pqs/meta/join_list.hpp>
#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/meta/type_list_alias.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct merge_list;

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct left_merge_list : push_front<
         typename merge_list<typename pop_front<Lhs_list>::type,Rhs_list,F>::type,
         typename front<Lhs_list>::type
      >{};

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct right_merge_list : push_front<
         typename merge_list<Lhs_list,typename pop_front<Rhs_list>::type, F>::type,
         typename front<Rhs_list>::type
      >{};

      template <typename... Lhs, typename... Rhs, typename F>
      struct merge_list<pqs::meta::type_list<Lhs...>,pqs::meta::type_list<Rhs...> ,F>{

          typedef pqs::meta::type_list<Lhs...> lhs_list;
          typedef pqs::meta::type_list<Rhs...> rhs_list;

          typedef typename front<lhs_list>::type lhs_front;
          typedef typename front<rhs_list>::type rhs_front;

          typedef typename pqs::meta::eval_if<
             //(lhs_front::value < rhs_front::value),
             typename F:: template apply<lhs_front, rhs_front>,
             left_merge_list<lhs_list,rhs_list,F>,
             right_merge_list<lhs_list,rhs_list,F>
          >::type type;
      }; 

      template <typename ...Lhs, typename F>
      struct merge_list<pqs::meta::type_list<Lhs...>,pqs::meta::type_list<> ,F > : pqs::meta::type_list<Lhs...>{};

      template <typename... Rhs, typename F>
      struct merge_list<pqs::meta::type_list<>,pqs::meta::type_list<Rhs...> ,F> : pqs::meta::type_list<Rhs...>{};

      template <typename F>
      struct merge_list<pqs::meta::type_list<>,pqs::meta::type_list<>,F> : pqs::meta::type_list<> {};

      template <typename List, typename F>
      struct merge_sort_impl{
         typedef pqs::meta::split_list<List> split_type;
         typedef typename split_type::lhs_type_list lhs_split;
         typedef typename split_type::rhs_type_list rhs_split;
         typedef typename merge_sort_impl<lhs_split, F>::type lhs_merge;
         typedef typename merge_sort_impl<rhs_split, F>::type rhs_merge;
         typedef typename merge_list<lhs_merge,rhs_merge, F>::type type;
      };

      template <typename T, typename F> 
      struct merge_sort_impl< pqs::meta::type_list<T> , F> : pqs::meta::type_list<T>{};

      template <typename F> 
      struct merge_sort_impl< pqs::meta::type_list<> , F> : pqs::meta::type_list<> {};

   }// detail

   /*
      F is a polymorphic functor of two args
      e.g  an example for a list that contains types modelling pqs::meta::_integral_constant
      This less_than function will sort the list in increasing order from left to right
      
      struct less_than {
         template <typename Lhs, typename Rhs>
         struct apply : std::integral_constant<bool,Lhs::value < Rhs::value>{};

      };
      
   */

   template <typename List, typename F>
   struct merge_sort ;

   template <template <typename...> class List, typename ... Elems, typename F>
   struct merge_sort<List<Elems...>,F >{

       typedef typename pqs::meta::type_list_alias<List<Elems...> >:: template apply<pqs::meta::type_list>::type list_in_alias_type;
       typedef typename detail::merge_sort_impl<list_in_alias_type,F>::type list_out_alias_type;
       typedef typename pqs::meta::type_list_alias<list_out_alias_type >:: template apply<List>::type type;
   };
      
}} // pqs::meta

#endif // PQS_META_MERGE_SORT_HPP_INCLUDED
