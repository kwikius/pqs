#ifndef PQS_META_IS_NUMERIC_HPP_INCLUDED
#define PQS_META_IS_NUMERIC_HPP_INCLUDED

/*
 Copyright (c) 2005-2013 Andy Little 

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
    Is T a numeric type
*/

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{ namespace meta{

    namespace impl{

       template <typename T, typename Where = void>
       struct is_numeric_impl : std::false_type{}; // : quan::meta::or_<std::is_arithmetic<ValueType>,quan::meta::is_angle<ValueType> >{};
  
       template <typename T>
       struct is_numeric_impl<
          T,
          typename pqs::where_<std::is_arithmetic<T> >::type
       > : std::true_type{};
       
    }//impl

    template <typename T>
    struct is_numeric : pqs::meta::impl::is_numeric_impl<typename pqs::meta::strip_cr<T>::type>{};

                
}}//pqs::meta

#endif

