#ifndef PQS_META_TYPE_LIST_HPP_INCLUDED
#define PQS_META_TYPE_LIST_HPP_INCLUDED
/*
 Copyright (c) 2003-2017 Andy Little.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see http://www.gnu.org/licenses./
 */

//#include <quan/concepts/meta/type_list.hpp>
#include <type_traits>
#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/meta/eval_if_else.hpp>

namespace pqs{ namespace meta{

   template <typename ... T> struct type_list{
      typedef type_list type;
      static const uint32_t length = sizeof...(T);
   };

   template <> struct type_list<>{
     typedef type_list type;
     static const uint32_t length = 0;
   };

   namespace impl{

      template <typename ... T>
      struct get_num_elements_impl<
         pqs::meta::type_list<T...>
      > : std::integral_constant<unsigned int, (sizeof...(T) )>{};

      template <typename T>
      struct push_back_impl<type_list<>,T >{
         typedef type_list<T> type;
      };

      template <typename ... L, typename T>
      struct push_back_impl<type_list<L...>,T >{
         typedef type_list<L...,T> type;
      };

      template <typename Front, typename ... List>
      struct pop_front_impl<type_list<Front,List...> >
      {
         typedef type_list<List...> type;
      };

      template <>
      struct pop_front_impl<type_list<> >
      {
         typedef pqs::undefined type;
      };

      template <typename...L, typename T>
      struct push_front_impl<type_list<L...> , T>
      {
         typedef type_list<T,L...> type;
      };

      template < typename Front, typename... List> 
      struct front_impl<type_list<Front,List...> >
      {
         typedef Front type;
      };

      template < typename Front> 
      struct front_impl<type_list<Front> >
      {
        typedef Front type;
      };

      template <>
      struct front_impl<type_list<> >
      {
         typedef pqs::undefined type;
      };

      template < typename Front ,typename... List> 
      struct back_impl< type_list<Front,List...> >
      {
          typedef typename back<type_list<List...> >::type type;
      };

      template < typename Back> 
      struct back_impl< type_list<Back> >
      {
         typedef Back type;
      };

      template <>
      struct back_impl<type_list<> >
      {
         typedef pqs::undefined type;
      };

      namespace detail {

         template <uint32_t N,typename List, typename other_list = type_list<> >
         struct type_list_get_first_n{

            typedef typename front<List>::type first_type;
            typedef typename pop_front<List>::type rest_type;
            typedef typename push_back<other_list,first_type>::type result_list_type;
            typedef typename pqs::meta::eval_if_else_c<
               result_list_type::length == N,
               result_list_type,
               type_list_get_first_n<N,rest_type,result_list_type>
            >::type type;
         };
      }

      template<typename... List>
      struct pop_back_impl<type_list<List...> >{
         typedef type_list<List...> list_type;
         typedef typename detail::type_list_get_first_n<
            list_type::length-1,list_type
         >::type type;
      };

      template< typename Last>
      struct pop_back_impl<type_list<Last> >{
         typedef type_list<> type;
      };

      template <>
      struct pop_back_impl<type_list<> >
      {
         typedef pqs::undefined type;
      };

      template <uint32_t N, typename... List>
      struct at_impl<N,type_list<List...> >{
         typedef type_list<List...> list_type;
         static_assert(N < list_type::length,"index out of range in pqs::meta::type_list");
         typedef typename pqs::meta::eval_if_else_c<
         N==0,
         pqs::meta::front<list_type>,
         pqs::meta::at<N-1,typename pqs::meta::pop_front<list_type>::type>
         >::type type; 
      };

      template <uint32_t N>
      struct at_impl<N,type_list<> >{
         typedef pqs::undefined type;
      };

   } // impl
   
}}

#endif // PQS_META_TYPE_LIST_HPP_INCLUDED
