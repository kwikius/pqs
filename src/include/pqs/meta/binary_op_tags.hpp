#ifndef PQS_META_BINARY_OP_TAGS_HPP
#define PQS_META_BINARY_OP_TAGS_HPP
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
    operator tags for use with binary_operation 
*/

namespace pqs{

   struct plus;
   struct minus;
   struct times;
   struct divides;

   struct less;
   struct less_equal;
   struct equal_to;
   struct not_equal_to;
   struct greater_equal;
   struct greater;

   struct modulus;

   struct div;     // integer/integer division op

   struct logical_or;
   struct logical_and;

   struct pow;

   struct equals;
   struct plus_equals;
   struct minus_equals;
   struct times_equals;
   struct divide_equals;
   struct modulus_equals;
   struct shift_left_equals;
   struct shift_right_equals;
   struct or_equals;
   struct and_equals;
   struct xor_equals;

   struct bit_or;
   struct bit_xor;
   struct bit_and;
   struct shift_left;
   struct shift_right;
    
       
}//pqs

#endif

