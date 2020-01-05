#ifndef PQS_BINARY_OP_IMPL_HPP_INCLUDED
#define PQS_BINARY_OP_IMPL_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

/*
 Copyright (c) 2005-2019 Andy Little 

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>
*/
/*
    The binary_operation struct has one member 'type' which 
    represents the type of the result of a binary operation.
    such as +, -, *, << ,!= ,== etc. The Op parameter 'token'
    is represented by the Op tokens provided in
    "pqs/meta/binary_op_tags.hpp".
    e.g for the result type of addition of 2 ints the typedef 
    would look like binary_op<int,plus,int>::type.

*/

#include <type_traits>

#include <pqs/bits/config.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/is_any_type.hpp>
#include <pqs/meta/is_numeric.hpp>
#include <pqs/meta/is_scalar.hpp>
#include <pqs/meta/binary_op_tags.hpp>
#include <pqs/meta/binary_operator_types.hpp>
#include <pqs/meta/is_runtime_type.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/not.hpp>

namespace pqs{ 

    namespace meta{
       template <typename A, typename B>
       struct are_arithmetic : pqs::meta::and_<
           std::is_arithmetic<A>,
           std::is_arithmetic<B>
       >{};
    }

    template <typename Tl, typename Op, typename TR>
    struct binary_op;

    template <typename Tl, typename Op, typename TR>
    struct is_valid_binary_op;

    namespace impl { 
       
       template <
          typename A,
          typename Op,
          typename B,
          typename Enable = void
       >
       struct binary_op_impl : pqs::undefined_arg<A,Op,B>{};

       template <
           typename Left, 
           typename Op, 
           typename Right
       >
       struct is_valid_binary_op_impl 
       : pqs::meta::is_any_type<typename pqs::binary_op<Left,Op,Right>::type>{};

       template < 
           typename A, 
           typename Op,
           typename B
       >
       struct binary_op_impl<
           A,Op,B,
           typename pqs::where_<           
               pqs::meta::is_assignment_operator<Op> 
           >::type
       >{
           typedef typename std::add_lvalue_reference<A>::type type;
       };

       template<
         typename A, 
         typename Op,
         typename B
       >
       struct binary_op_impl<
           A,Op,B,
           typename pqs::where_<
               pqs::meta::and_<
                  pqs::meta::is_scalar<A>,
                  pqs::meta::is_scalar<B>,
                  pqs::meta::is_comparison_operator<Op>,
                  pqs::meta::or_<
                     pqs::meta::is_runtime_type<A>,
                     pqs::meta::is_runtime_type<B>
                  >,
                  pqs::meta::or_<
                     pqs::is_valid_binary_op<A,minus,B>,
                     pqs::meta::and_<
                        std::is_same<A,bool>,
                        std::is_same<B,bool>
                     >
                  >
               >
           >::type
       >{
         typedef bool type;
       };

      template<>
      struct binary_op_impl<
         bool, logical_or, bool
      >{
         typedef bool type;
      };
      
      template<>
      struct binary_op_impl<
         bool, logical_and, bool
      >{
         typedef bool type;
      };
      
      template<>
      struct binary_op_impl<
         bool, bit_and, bool
      >{
         typedef bool type;
      };

      template <
       typename A,
       typename B
      >
      struct binary_op_impl<
        A , plus, B , 
        typename pqs::where_<
            pqs::meta::are_arithmetic<A,B>
        >::type
      > : std::common_type<A,B>{};

      template <
       typename A,
       typename B
      >
      struct binary_op_impl<
        A , minus, B , 
        typename pqs::where_<
            pqs::meta::are_arithmetic<A,B>
        >::type
       > : std::common_type<A,B>{};

      template <
       typename A,
       typename B
      >
      struct binary_op_impl<
        A , bit_or, B , 
        typename pqs::where_<
           pqs::meta::are_arithmetic<A,B>
        >::type
      > : std::common_type<A,B>{};

      template <
       typename A,
       typename B
      >
      struct binary_op_impl<
        A , bit_and, B , 
        typename pqs::where_<
            pqs::meta::are_arithmetic<A,B>
        >::type
      > : std::common_type<A,B>{};

      template <
         typename A,
         typename B
      >
      struct binary_op_impl<
        A , times, B , 
        typename pqs::where_<
            pqs::meta::are_arithmetic<A,B>
        >::type
      > : std::common_type<A,B>{};

      template <
         typename A,
         typename B
      >
      struct binary_op_impl<
        A , divides, B , 
        typename pqs::where_<
            pqs::meta::are_arithmetic<A,B>
        >::type
      > : std::common_type<A,B>{};

/*
      template <
         typename A,
         typename B
      >
      struct binary_op_impl<
        A , pqs::to_power, B , 
        typename pqs::where_<
            and_<
               std::is_arithmetic<A>,
               and_<
                  not_<eq_one<B> >,
                  not_<eq_zero<B> >
               >
            >
        >::type
      > : std::common_type<
            A,
            pqs::quantity_traits::default_value_type
          >{};
*/

   }//impl
   
}//pqs

#endif
