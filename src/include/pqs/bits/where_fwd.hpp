#ifndef PQS_WHERE_FWD_HPP_INCLUDED
#define PQS_WHERE_FWD_HPP_INCLUDED

/*
 Copyright (c) 2005 - 2019 Andy Little 

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

namespace pqs{

   template <bool C, typename T= void>
   struct where_c;

   template <typename C, typename T = void>
   struct where_ ;

   template <bool C, typename T>
   struct eval_where_c;

   template <typename C, typename T>
   struct eval_where ;

   template <typename C,typename T = void>
   struct where_not;

   template <typename C,typename T>
   struct eval_where_not;

}

#endif

