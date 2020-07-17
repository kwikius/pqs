#ifndef PQS_META_AND_HPP_INCLUDED
#define PQS_META_AND_HPP_INCLUDED
/*
 Copyright (c) 2006-2013 Andy Little 

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

#include <pqs/bits/meta/eval_if.hpp>

namespace pqs{namespace meta{
   
   template<typename Lhs, typename... Args > struct and_ : eval_if<
      Lhs, and_<Args...>, std::false_type
   >::type {};
     
   template<typename C1, typename C2>
   struct and_<C1,C2>: eval_if<
      C1,C2,
      std::false_type
   >::type{};

}} // pqs::meta

#endif  // PQS_META_AND_HPP_INCLUDED
