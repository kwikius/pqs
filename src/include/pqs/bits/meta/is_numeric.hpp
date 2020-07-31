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

namespace pqs{ namespace meta{

    namespace impl{

       template <typename T>
       struct is_numeric_impl : std::false_type{}; 
  
       template <typename T>
         requires std::is_arithmetic_v<T>
       struct is_numeric_impl< T > : std::true_type{};
       
    }//impl

    template <typename T>
    struct is_numeric : pqs::meta::impl::is_numeric_impl< std::remove_cvref_t<T> >{};

                
}}//pqs::meta

#endif

