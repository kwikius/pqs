#ifndef PQS_META_EVAL_IF_HPP_INCLUDED
#define PQS_META_EVAL_IF_HPP_INCLUDED

#if 1

#include <pqs/meta/type_list.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template <typename ... T>
      struct eval_if_list;

      template <typename T>
      struct make_eval_if_list;

      template <typename ...T>
      struct make_eval_if_list< pqs::meta::type_list<T...> >{
         typedef eval_if_list<T...> type;
      };

   }

   // e,g
   // eval_if_c<bool, Fun1, BoolFun2, Fun2, BooolFun3, Fun3,BoolFun4, Fun4, Fun5>
   template <bool b, typename FT, typename... Rest>
   struct eval_if_c {
      typedef typename FT::type type;
   };

   // e,g
   // eval_if_c<BoolFun1, Fun1, BoolFun2, Fun2, BooolFun3, Fun3,BoolFun4, Fun4, Fun5>
   template <typename C, typename FT, typename... Rest>
   struct eval_if : eval_if_c<C::type::value, FT, Rest...>{};

   template <typename FT, typename FF>
   struct eval_if_c<false,FT,FF> :FF{};

   template <typename FT, typename ... FF>
   struct eval_if_c<true, FT, pqs::meta::detail::eval_if_list<FF...> > : FT{};

   template <typename FT, typename ...FF>
   struct eval_if_c<false, FT, pqs::meta::detail::eval_if_list<FF...> > : eval_if_c<false,FT, FF...> {};

   template <typename FT, typename... FF>
   struct eval_if_c<false,FT,FF...> {
      typedef pqs::meta::type_list<FF...> list;
      typedef typename pqs::meta::front<list>::type cond;
      typedef typename pqs::meta::pop_front<list>::type list1;
      typedef typename pqs::meta::front<list1>::type FT1;
      typedef typename pqs::meta::pop_front<list1>::type next_list;
      typedef typename detail::make_eval_if_list<next_list>::type eval_list;
      
      typedef typename eval_if<
         cond,
         FT1,
         eval_list
      >::type type;
   };

}} // pqs::meta


#else

namespace pqs{

   namespace meta{

      template <bool B, typename TrueFunction, typename FalseFunction>
      struct eval_if_c{
         typedef typename TrueFunction::type type;
      };

      template <typename TrueFunction,typename FalseFunction>
      struct eval_if_c<false,TrueFunction,FalseFunction> {
         typedef typename FalseFunction::type type;
      };

      template<typename C, typename TrueFunction, typename FalseFunction>
      struct eval_if : eval_if_c<((C::type::value)!=0),TrueFunction,FalseFunction>{};

}} // pqs::meta

#endif

#endif // PQS_META_EVAL_IF_HPP_INCLUDED
