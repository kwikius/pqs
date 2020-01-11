#ifndef PQS_META_BINARY_OPERATOR_TRAITS_HPP_INCLUDED
#define PQS_META_BINARY_OPERATOR_TRAITS_HPP_INCLUDED
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
    more refined traits of operators
    should probably be:
    binary_operator_expression_family<op>::value;
    binary_operator_associates_left<op>::value
    note commutivity is naff and will be removed!
    might need to be specialised
*/

//#include <pqs/meta/binary_operator_parameters.hpp>
#include <type_traits>
#include <pqs/meta/binary_op_tags.hpp>

namespace pqs { namespace meta{

   enum class op_associativity_t { left, right};

   enum class op_class_t{
      assignment = 1,
      conditional=2,
      logical_or=3,
      logical_and=4,
      inclusive_or=5,
      exclusive_or=6,
      bit_and=7,
      equality=8, 
      relational=9,
      shift=10,
      additive=11,
      multiplicative=12,
      pow = 13
   };

    template <typename Op>
    struct op_class;

    template <typename Op>
    struct op_associativity;

    template <>
    struct op_associativity <pqs::equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::plus_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::plus_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::minus_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::minus_equals> {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::times_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::times_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::divide_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::divide_equals> {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::modulus_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::modulus_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::shift_left_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::shift_left_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::shift_right_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::shift_right_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::or_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::or_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::xor_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::xor_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::and_equals>  { static constexpr op_associativity_t value = op_associativity_t::left ;};
    template <>
    struct op_class<pqs::and_equals>  {static constexpr op_class_t value = op_class_t::assignment;};

    template <>
    struct op_associativity <pqs::logical_or>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::logical_or>  {static constexpr op_class_t value = op_class_t::logical_or;};

    template <>
    struct op_associativity <pqs::logical_and>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::logical_and>  {static constexpr op_class_t value = op_class_t::logical_and;};

    template <>
    struct op_associativity <pqs::bit_or>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::bit_or>  {static constexpr op_class_t value = op_class_t::inclusive_or;};

    template <>
    struct op_associativity <pqs::bit_xor>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::bit_xor> {static constexpr op_class_t value = op_class_t::exclusive_or;};

    template <>
    struct op_associativity <pqs::bit_and>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::bit_and>  {static constexpr op_class_t value = op_class_t::bit_and;};

    template <>
    struct op_associativity <pqs::equal_to>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::equal_to>  {static constexpr op_class_t value = op_class_t::equality;};

    template <>
    struct op_associativity <pqs::not_equal_to>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::not_equal_to>  {static constexpr op_class_t value = op_class_t::equality;};

    template <>
    struct op_associativity <pqs::less>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::less>  {static constexpr op_class_t value = op_class_t::relational;};

    template <>
    struct op_associativity <pqs::less_equal>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::less_equal>  {static constexpr op_class_t value = op_class_t::relational;};

    template <>
    struct op_associativity <pqs::greater_equal>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::greater_equal>  {static constexpr op_class_t value = op_class_t::relational;};

    template <>
    struct op_associativity <pqs::greater>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::greater>  {static constexpr op_class_t value = op_class_t::relational;};

    template <>
    struct op_associativity <pqs::shift_left>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::shift_left>  {static constexpr op_class_t value = op_class_t::shift;};
    
    template <>
    struct op_associativity <pqs::shift_right>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::shift_right>  {static constexpr op_class_t value = op_class_t::shift;};

    template <>
    struct op_associativity <pqs::plus>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::plus>  {static constexpr op_class_t value = op_class_t::additive;};

    template <>
    struct op_associativity <pqs::minus>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::minus>  {static constexpr op_class_t value = op_class_t::additive;};

    template <>
    struct op_associativity <pqs::times>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::times>  {static constexpr op_class_t value = op_class_t::multiplicative;};

    template <>
    struct op_associativity <pqs::divides>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::divides> {static constexpr op_class_t value = op_class_t::multiplicative;};

    template <>
    struct op_associativity <pqs::div>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::div>  {static constexpr op_class_t value = op_class_t::multiplicative;};

    template <>
    struct op_associativity <pqs::modulus>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::modulus>  {static constexpr op_class_t value = op_class_t::multiplicative;};

    template <>
    struct op_associativity <pqs::to_power>  { static constexpr op_associativity_t value = op_associativity_t::right ;};
    template <>
    struct op_class<pqs::to_power>  {static constexpr op_class_t value = op_class_t::pow;};

    template<typename Op>
    struct is_assignment_operator : std::integral_constant<bool,(op_class<Op>::value == op_class_t::assignment)>{};

    template<typename Op >
    struct is_conditional_operator : std::integral_constant<bool,(op_class<Op>::value == op_class_t::conditional)>{};

    template <typename Op>
    struct is_comparison_operator : std::integral_constant<
       bool,
       ( (op_class<Op>::value == op_class_t::equality) ||  (op_class<Op>::value == op_class_t::relational) )
    >{};

   template< 
        typename Op
    >
    struct is_logical_operator : std::integral_constant<bool,
       ( (op_class<Op>::value == op_class_t::logical_or) || (op_class<Op>::value == op_class_t::logical_and) ) 
    >{};

    template< 
        typename Op
    > struct is_arithmetic_operator : std::integral_constant<bool,
       ( (op_class<Op>::value == op_class_t::additive) || (op_class<Op>::value == op_class_t::multiplicative) ) 
    >{};

#if 0

    template< 
        typename Op
    >
    struct is_logical_or_operator{
        typedef is_logical_or_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::logical_or_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_logical_and_operator{
        typedef is_logical_and_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::logical_and_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_inclusive_or_operator{
        typedef is_inclusive_or_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::inclusive_or_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_exclusive_or_operator{
        typedef is_exclusive_or_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::exclusive_or_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_and_operator{
        typedef is_and_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::and_expression))
        };
    };

     template< 
        typename Op
    >
    struct is_bit_operator 
      : or_< 
            is_and_operator<Op>,
            or_<
             is_inclusive_or_operator<Op>,
             is_exclusive_or_operator<Op>
            >
      >{};

    template< 
        typename Op
    >
    struct is_equality_operator{
        typedef is_equality_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::equality_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_relational_operator{
        typedef is_relational_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::relational_expression))
        };
    };
    
   template< 
        typename Op
    >
    struct is_logical_operator : or_<
      is_logical_and_operator<Op>,
      or_<
         is_logical_or_operator<Op>,
         or_<
            is_relational_operator<Op>,
            is_equality_operator<Op>
         >
      >
    >{};

    template< 
        typename Op
    >
    struct is_shift_operator{
        typedef is_shift_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::shift_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_additive_operator{
        typedef is_additive_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::additive_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_multiplicative_operator{
        typedef is_multiplicative_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::multiplicative_expression))
        };
    };

    template< 
        typename Op
    >
    struct is_pow_operator{
        typedef is_pow_operator type;
        enum{ 
        value =
           (binary_operator_traits<Op>::expression_family
            == static_cast<int>(binary_operator_parameters::pow_expression))
        };
    };
    
#endif
}}//quan::meta

#endif
