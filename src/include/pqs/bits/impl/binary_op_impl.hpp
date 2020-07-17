#ifndef PQS_BINARY_OP_IMPL_HPP_INCLUDED
#define PQS_BINARY_OP_IMPL_HPP_INCLUDED


/*
 Copyright (c) 2005-2020 Andy Little 

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
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/meta/is_any_type.hpp>
#include <pqs/bits/meta/binary_op_tags.hpp>
#include <pqs/bits/meta/binary_operator_types.hpp>
#include <pqs/bits/meta/is_runtime_type.hpp>
#include <pqs/bits/meta/or.hpp>
#include <pqs/bits/meta/and.hpp>
#include <pqs/bits/meta/not.hpp>

namespace pqs{ 

    namespace meta{

       template <typename A, typename B>
       struct are_arithmetic : pqs::meta::and_<
           std::is_arithmetic<A>,
           std::is_arithmetic<B>
       >{};

    } //meta

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

       template < typename A, typename Op, typename B>
          requires
             pqs::meta::is_assignment_operator<Op>::value
             && std::is_assignable_v<A,B>
       struct binary_op_impl<A, Op,B> : std::add_lvalue_reference<A>{};

      template < typename A, typename Op, typename B>
         requires  
            pqs::meta::and_<
               pqs::meta::are_arithmetic<A,B>,
               pqs::meta::or_<
                  pqs::meta::is_comparison_operator<Op>,
                  pqs::meta::is_logical_operator<Op>
               >,
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
             >::value
       struct binary_op_impl<A,Op,B>{
          typedef bool type;
       };

      template < typename A, typename Op, typename B>
         requires   
            pqs::meta::or_<
               pqs::meta::and_<
                  pqs::meta::are_arithmetic<A,B>,
                  pqs::meta::is_arithmetic_operator<Op>
               >,
               pqs::meta::and_<
                  std::is_integral<A>,
                  std::is_integral<B>,
                  std::integral_constant<bool,(
                     (pqs::meta::op_class<Op>::value == pqs::meta::op_class_t::inclusive_or) ||
                     (pqs::meta::op_class<Op>::value == pqs::meta::op_class_t::exclusive_or) ||
                     (pqs::meta::op_class<Op>::value == pqs::meta::op_class_t::bit_and) ||
                     (pqs::meta::op_class<Op>::value == pqs::meta::op_class_t::shift)
                  )>
               >
            >::value
      struct binary_op_impl<A,Op,B> : std::common_type<A,B>{};

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
