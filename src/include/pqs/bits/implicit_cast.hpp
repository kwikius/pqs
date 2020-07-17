#ifndef PQS_BITS_IMPLICIT_CAST_HPP_INCLUDED
#define PQS_BITS_IMPLICIT_CAST_HPP_INCLUDED

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

#include <pqs/bits/meta/identity.hpp>
#include <type_traits>

namespace pqs{

#if 1

// see link for this implementation
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0758r0.html
template <class T, class U>
constexpr inline 
T implicit_cast(U&& u) 
  noexcept(std::is_nothrow_convertible_v<U, T>) 
{
  return std::forward<U>(u);
}

#else

   template<typename T>
   constexpr inline
   T implicit_cast(typename meta::identity<T>::type in)
   {
      return in;
   }

#endif
}

#endif  // PQS_BITS_IMPLICIT_CAST_HPP_INCLUDED
