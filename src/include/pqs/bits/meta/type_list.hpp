#ifndef PQS_META_TYPE_LIST_HPP_INCLUDED
#define PQS_META_TYPE_LIST_HPP_INCLUDED
/*
 Copyright (c) 2003-2020 Andy Little.

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

#include <type_traits>
#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/meta/eval_if_else.hpp>

namespace pqs{ namespace meta{

   template <typename ... T> struct type_list{
      using type = type_list;
      static constexpr uint32_t length = sizeof...(T);
   };

   template <> struct type_list<>{
     using type = type_list;
     static constexpr uint32_t length = 0;
   };

   namespace impl{

      template <typename ... T>
      struct get_num_elements_impl<
         pqs::meta::type_list<T...>
      > : std::integral_constant<unsigned int, (sizeof...(T) )>{};

      template <typename T>
      struct push_back_impl<type_list<>,T >{
         using type = type_list<T>;
      };

      template <typename ... L, typename T>
      struct push_back_impl<type_list<L...>,T >{
         using type = type_list<L...,T>;
      };

      template <typename Front, typename ... List>
      struct pop_front_impl<type_list<Front,List...> >
      {
         using type = type_list<List...>;
      };

      template <>
      struct pop_front_impl<type_list<> >
      {
         using type = pqs::undefined;
      };

      template <typename...L, typename T>
      struct push_front_impl<type_list<L...> , T>
      {
         using type = type_list<T,L...>;
      };

      template < typename Front, typename... List> 
      struct front_impl<type_list<Front,List...> >
      {
         using type = Front;
      };

      template < typename Front> 
      struct front_impl<type_list<Front> >
      {
          using type = Front;
      };

      template <>
      struct front_impl<type_list<> >
      {
         using type = pqs::undefined;
      };

      template < typename Front ,typename... List> 
      struct back_impl< type_list<Front,List...> >
      {
         using type = back_t<type_list<List...> >;
      };

      template < typename Back> 
      struct back_impl< type_list<Back> >
      {
         using type = Back;
      };

      template <>
      struct back_impl<type_list<> >
      {
         using type = pqs::undefined;
      };

      namespace detail {

         template <uint32_t N,typename List, typename other_list = type_list<> >
         struct type_list_get_first_n{

            using first_type = front_t<List>;
            using rest_type = pop_front_t<List>;
            using result_list_type = push_back_t<other_list,first_type>;
            using type = typename pqs::meta::eval_if_else_c<
               result_list_type::length == N,
               result_list_type,
               type_list_get_first_n<N,rest_type,result_list_type>
            >::type;
         };
      }

      template<typename... List>
      struct pop_back_impl<type_list<List...> >{
         using list_type = type_list<List...>;
         using type = typename detail::type_list_get_first_n<
            list_type::length-1,list_type
         >::type;
      };

      template< typename Last>
      struct pop_back_impl<type_list<Last> >{
         using type = type_list<> ;
      };

      template <>
      struct pop_back_impl<type_list<> >
      {
         using type = pqs::undefined;
      };

      template <uint32_t N, typename... List>
      struct at_impl<N,type_list<List...> >{
         using list_type = type_list<List...>;
         static_assert(N < list_type::length,"index out of range in pqs::meta::type_list");
         using type = typename pqs::meta::eval_if_else_c<
            N==0,
            pqs::meta::front<list_type>,
            pqs::meta::at<N-1,pqs::meta::pop_front_t<list_type> >
         >::type; 
      };

      template <uint32_t N>
      struct at_impl<N,type_list<> >{
         using type = pqs::undefined;
      };

   } // impl
}} //pqs::meta

#endif // PQS_META_TYPE_LIST_HPP_INCLUDED
