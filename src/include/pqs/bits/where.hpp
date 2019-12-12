#ifndef PQS_WHERE_HPP_INCLUDED
#define PQS_WHERE_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

/*
 Copyright (c) 2007 - 2013 Andy Little 

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

//source, acknowledgements
//--------------
//"C++ Templates The Complete guide, David Vandevoorde and Nicolai M. Josuttis. Section 8.3.1
// Copyright 2003 Pearson Education Inc
//-------------


#include <pqs/bits/where_fwd.hpp>

namespace pqs{

   template <bool C, typename T>
   struct where_c{
      typedef T type;
   };

   template <bool C, typename T>
   struct eval_where_c{
      typedef typename T::type type;
   };

   template <typename T>
   struct where_c<false, T>{};

   template <typename T>
   struct eval_where_c<false, T>{};

   template <typename C, typename T >
   struct where_ : where_c<(C::value),T>{};

   template <typename C, typename T >
   struct eval_where : eval_where_c<(C::value),T>{};

   template <typename C,typename T>
   struct where_not : where_c<(!(C::value)),T>{};

   template <typename C,typename T>
   struct eval_where_not : eval_where_c<(!(C::value)),T>{};

}

#endif

