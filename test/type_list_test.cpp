/*
Copyright (c) 2003-2014 Andy Little.

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

#include <quan_matters/test/test.hpp>
#include <type_traits>

#include <pqs/meta/type_list.hpp>

namespace {
   struct my_type;
}

void type_list_test()
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
