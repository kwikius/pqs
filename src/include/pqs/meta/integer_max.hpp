#ifndef PQS_META_INTEGER_MAX_HPP_INCLUDED
#define PQS_META_INTEGER_MAX_HPP_INCLUDED

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
 along with this program. If not, see http://www.gnu.org/licenses./
 */

#include <climits>
#include <type_traits>

namespace pqs{ namespace meta{

   template <typename T>
   struct integer_max;

   template<>
   struct integer_max<signed char> : std::integral_constant<signed char,SCHAR_MAX>{};
   
   template<>
   struct integer_max<unsigned char> : std::integral_constant<unsigned char,UCHAR_MAX>{};
 
   template<>
   struct integer_max<signed short> : std::integral_constant<signed short,SHRT_MAX>{};
 
   template<>
   struct integer_max<unsigned short> : std::integral_constant<unsigned short,USHRT_MAX>{};
 
   template<>
   struct integer_max<signed int> : std::integral_constant<signed int,INT_MAX>{};
  
   template<>
   struct integer_max<unsigned int> : std::integral_constant<unsigned int,UINT_MAX>{};
 
   template<>
   struct integer_max<signed long> : std::integral_constant<signed long,LONG_MAX>{};
  
   template<>
   struct integer_max<unsigned long> : std::integral_constant<unsigned long,ULONG_MAX>{};
  
   template<>
   struct integer_max<signed long long> : std::integral_constant<signed long long,LLONG_MAX>{};
  
   template<>
   struct integer_max<unsigned long long> : std::integral_constant<unsigned long long,ULLONG_MAX>{};
 
}} //pqs::meta

#endif

