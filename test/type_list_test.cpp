/*
Copyright (c) 2003-2019 Andy Little.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see http://www.gnu.org/licenses.
*/

#include "test.hpp"

#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/type_list.hpp>
#include <pqs/meta/split_list.hpp>
#include <pqs/meta/join_list.hpp>


namespace pqs{ namespace meta{

      template <typename Lhs_list, typename Rhs_list>
      struct merge;

      template <typename Lhs_list, typename Rhs_list>
      struct left_merge : push_front<
         typename merge<typename pop_front<Lhs_list>::type,Rhs_list>::type,
         typename front<Lhs_list>::type
      >{};

      template <typename Lhs_list, typename Rhs_list>
      struct right_merge : push_front<
         typename merge<Lhs_list,typename pop_front<Rhs_list>::type>::type,
         typename front<Rhs_list>::type
      >{};

      template <typename... Lhs, typename... Rhs>
      struct merge<type_list<Lhs...>,type_list<Rhs...> >{

          typedef type_list<Lhs...> lhs_list;
          typedef type_list<Rhs...> rhs_list;

          typedef typename front<lhs_list>::type lhs_front;
          typedef typename front<rhs_list>::type rhs_front;

          typedef typename pqs::meta::eval_if_c<
             (lhs_front::value < rhs_front::value),
             left_merge<lhs_list,rhs_list>,
             right_merge<lhs_list,rhs_list>
          >::type type;
      }; 

      template <typename ...Lhs>
      struct merge<type_list<Lhs...>,type_list<> > : type_list<Lhs...>{};

      template <typename... Rhs>
      struct merge<type_list<>,type_list<Rhs...> > : type_list<Rhs...>{};

      template <>
      struct merge<type_list<>,type_list<> > : type_list<> {};

      template <typename List>
      struct merge_sort{
         typedef pqs::meta::split_list<List> split_type;
         typedef typename split_type::lhs_type_list lhs_split;
         typedef typename split_type::rhs_type_list rhs_split;
         typedef typename merge_sort<lhs_split>::type lhs_merge;
         typedef typename merge_sort<rhs_split>::type rhs_merge;
         typedef typename merge<lhs_merge,rhs_merge>::type type;
      };

      template <typename T> 
      struct merge_sort< type_list<T> > : type_list<T>{};

      template <> 
      struct merge_sort< type_list<> > : type_list<> {};

}}

namespace {
   // used in tests
   struct my_type;

   template <int N>
   struct index;
}

namespace {

   // simple sorting
   template <int N> struct v : std::integral_constant<int,N>{};

   void sort_test1()
   {
      typedef pqs::meta::type_list<v<10> > list;
      typedef pqs::meta::merge_sort<list>::type result_type;
      typedef list expected_type;
      QUAN_CHECK((std::is_same<result_type,expected_type>::value))
   }

      void sort_test2()
   {
      typedef pqs::meta::type_list<v<10>,v<-3> > list;
      typedef pqs::meta::merge_sort<list>::type result_type;
      typedef pqs::meta::type_list<v<-3>,v<10> > expected_type;
      QUAN_CHECK((std::is_same<result_type,expected_type>::value))
   }

      void sort_test3()
   {
      typedef pqs::meta::type_list<v<10>,v<-10>,v<4>,v<0>,v<2>,v<1>,v<3> > list;
      typedef pqs::meta::merge_sort<list>::type result_type;
      typedef pqs::meta::type_list<v<-10>,v<0>,v<1>,v<2>,v<3>,v<4>,v<10> > expected_type;
      QUAN_CHECK((std::is_same<result_type,expected_type>::value))
   }

   void sort_test()
   {
      sort_test1();
      sort_test2();
      sort_test3();
   }

   void odd_split_test()
   {
       // odd list length case
       typedef pqs::meta::type_list<int, float,index<2>, double,my_type>list;
 
       typedef pqs::meta::split_list<list>::lhs_type_list lhs;
       typedef pqs::meta::split_list<list>::rhs_type_list rhs;
      
       QUAN_CHECK((std::is_same<lhs,pqs::meta::type_list<int,float> >::value))
       QUAN_CHECK((std::is_same<rhs,pqs::meta::type_list<index<2>,double,my_type> >::value))

       typedef pqs::meta::join_list<lhs,rhs>::type list1;
       QUAN_CHECK((std::is_same<list1,list>::value))

   }

   void even_split_test()
   {
       // even list length case length 6
       typedef pqs::meta::type_list<int, float,index<2>, double,my_type,std::integral_constant<bool,true> >list;
 
       typedef pqs::meta::split_list<list>::lhs_type_list lhs;
       typedef pqs::meta::split_list<list>::rhs_type_list rhs;
      
       QUAN_CHECK((std::is_same<lhs,pqs::meta::type_list<int,float,index<2>> >::value))
       QUAN_CHECK((std::is_same<rhs,pqs::meta::type_list<double,my_type,std::integral_constant<bool,true>> >::value))

       typedef pqs::meta::join_list<lhs,rhs>::type list1;
       QUAN_CHECK((std::is_same<list1,list>::value))
   }
   
   void empty_split_test()
   {
       typedef pqs::meta::type_list<> list;
       typedef pqs::meta::split_list<list>::lhs_type_list lhs;
       typedef pqs::meta::split_list<list>::rhs_type_list rhs;
      
       QUAN_CHECK((std::is_same<lhs,pqs::meta::type_list<> >::value))
       QUAN_CHECK((std::is_same<rhs,pqs::meta::type_list<> >::value))

       typedef pqs::meta::join_list<lhs,rhs>::type list1;
       QUAN_CHECK((std::is_same<list1,list>::value))
    
   }

   // currently puts the one element on rhs
   void length_one_split_test()
   {
       typedef pqs::meta::type_list<float> list;
       typedef pqs::meta::split_list<list>::lhs_type_list lhs;
       typedef pqs::meta::split_list<list>::rhs_type_list rhs;
      
       QUAN_CHECK((std::is_same<lhs,pqs::meta::type_list<> >::value))
       QUAN_CHECK((std::is_same<rhs,pqs::meta::type_list<float> >::value))
   }

   void split_test()
   {
      odd_split_test();
      even_split_test();
      empty_split_test();
      length_one_split_test();
   }

   void at_test()
   {
      typedef pqs::meta::type_list<index<0>,index<1>,index<2>,index<3> > list;
      QUAN_CHECK(( std::is_same<pqs::meta::at<0,list>::type, index<0> >::value))
      QUAN_CHECK(( std::is_same<pqs::meta::at<1,list>::type, index<1> >::value))
      QUAN_CHECK(( std::is_same<pqs::meta::at<2,list>::type, index<2> >::value))
      QUAN_CHECK(( std::is_same<pqs::meta::at<3,list>::type, index<3> >::value))
   }

   void push_pop_test()
   {
      using pqs::meta::type_list; 
      using pqs::meta::push_back;
      using pqs::meta::push_front;
      using pqs::meta::pop_front;
      using pqs::meta::pop_back;
      using pqs::meta::front;
      using pqs::meta::back;
      using pqs::meta::at;
      using pqs::meta::get_num_elements;

      typedef type_list<> t1;

      static_assert(std::is_same<t1,type_list<> >::value, "error");

      typedef push_back<t1,int>::type t2;

      static_assert(std::is_same<at<0,t2>::type,int>::value, "error");
 
      static_assert(std::is_same<t2,type_list<int> >::value, "error");

      typedef push_back<t2,double>::type t3;

      static_assert(std::is_same<t3,type_list<int,double> >::value, "error");
      static_assert(std::is_same<front<t3>::type,int>::value,"error");
      static_assert(std::is_same<back<t3>::type,double>::value,"error");
      static_assert(std::is_same<pop_back<t3>::type, t2>::value,"error");
      static_assert(std::is_same<at<1,t3>::type,double>::value,"error");
      static_assert(get_num_elements<t3>::value == 2, "error");

      typedef pop_front<t3>::type t4;

      static_assert (std::is_same<t4,type_list<double> >::value, "error");

      typedef push_front<t4,int>::type t5;

      static_assert (std::is_same<t5,t3 >::value, "error");
     
      static_assert(std::is_same<t5,type_list<int,double> >::value, "error");

      typedef push_front<t1,bool>::type t6;

      static_assert(std::is_same<front<t6>::type,bool>::value,"error");

      static_assert(std::is_same<back<t6>::type,bool>::value,"error");
      
      typedef push_back<t5,my_type>::type t7;
      static_assert(std::is_same<t7,type_list<int,double,my_type> >::value, "error");
      static_assert(std::is_same<at<2,t7>::type,my_type>::value, "error");
      static_assert(get_num_elements<t7>::value == 3, "error");
   }
}



void type_list_test()
{
   push_pop_test();
   split_test();
   at_test();
   sort_test();
}
