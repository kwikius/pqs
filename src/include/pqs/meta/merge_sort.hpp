#ifndef PQS_META_MERGE_SORT_HPP_INCLUDED
#define PQS_META_MERGE_SORT_HPP_INCLUDED

#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/type_list.hpp>
#include <pqs/meta/split_list.hpp>
#include <pqs/meta/join_list.hpp>
#include <pqs/meta/type_list_alias.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct merge_list;

      template <typename Lhs_list, typename Rhs_list, typename F>
      using merge_list_t = typename merge_list<
         Lhs_list, Rhs_list,F
      >::type;

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct left_merge_list : push_front<
         merge_list_t<pop_front_t<Lhs_list>,Rhs_list,F>,
         front_t<Lhs_list>
      >{};

      template <typename Lhs_list, typename Rhs_list, typename F>
      struct right_merge_list : push_front<
         merge_list_t<Lhs_list,pop_front_t<Rhs_list>, F>,
         front_t<Rhs_list>
      >{};

      template <typename... Lhs, typename... Rhs, typename F>
      struct merge_list<
            meta::type_list<Lhs...>,
            meta::type_list<Rhs...> ,
            F
      >{
         using lhs_list = meta::type_list<Lhs...>;
         using rhs_list = meta::type_list<Rhs...>;

         using type = meta::eval_if_t<
            typename F:: template apply<
               front_t<lhs_list>, front_t<rhs_list>
            >,
            left_merge_list<lhs_list,rhs_list,F>,
            right_merge_list<lhs_list,rhs_list,F>
         >;
      }; 

      template <typename ...Lhs, typename F>
      struct merge_list<
         meta::type_list<Lhs...>,
         meta::type_list<> ,F > 
      : meta::type_list<Lhs...>{};

      template <typename... Rhs, typename F>
      struct merge_list<
         meta::type_list<>,
         meta::type_list<Rhs...> ,F> 
      : meta::type_list<Rhs...>{};

      template <typename F>
      struct merge_list<
         meta::type_list<>,
         meta::type_list<>,F> 
      : meta::type_list<> {};

      template <typename List, typename F>
      struct merge_sort_impl{
         using split_type = meta::split_list<List>;
         using lhs_split = typename split_type::lhs_type_list;
         using rhs_split = typename split_type::rhs_type_list;
         using lhs_merge = typename merge_sort_impl<lhs_split, F>::type;
         using rhs_merge = typename merge_sort_impl<rhs_split, F>::type;
         using type = merge_list_t<lhs_merge,rhs_merge, F>;
      };

      template <typename T, typename F> 
      struct merge_sort_impl< meta::type_list<T> , F> 
      : meta::type_list<T>{};

      template <typename F> 
      struct merge_sort_impl< meta::type_list<> , F> 
      : meta::type_list<> {};

   }// detail

   /*
      F is a polymorphic functor of two args
      e.g  an example for a list that contains types modelling meta::_integral_constant
      This less_than function will sort the list in increasing order from left to right
      
      struct less_than {
         template <typename Lhs, typename Rhs>
         struct apply : std::integral_constant<bool,Lhs::value < Rhs::value>{};

      };
      
   */

   template <typename List, typename F>
   struct merge_sort ;

   template <
      template <typename...> class List, 
      typename ... Elems, typename F
   >
   struct merge_sort<List<Elems...>,F >{

      using list_in_alias_type = 
         typename meta::type_list_alias<
            List<Elems...> 
         >:: template apply<
            meta::type_list
         >::type;

      using list_out_alias_type =
         typename detail::merge_sort_impl<
            list_in_alias_type,F
         >::type;

      using type = 
         typename meta::type_list_alias<
            list_out_alias_type 
         >:: template apply<List>::type;
   };

   template <typename List, typename F>
   using merge_sort_t  = typename merge_sort<List,F>::type;
      
}} // pqs::meta

#endif // PQS_META_MERGE_SORT_HPP_INCLUDED
