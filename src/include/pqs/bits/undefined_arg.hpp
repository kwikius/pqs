#ifndef PQS_UNDEFINED_ARG_HPP_INCLUDED
#define PQS_UNDEFINED_ARG_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

/*
 Copyright (c) 2019 Andy Little 

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

   /*
     TODO change to undefined_arg<T...>, will show args info then
   */

   template <typename ... Args>
   struct undefined_arg {
     
      typedef undefined_arg type;

      private:
         undefined_arg() = delete;
         undefined_arg(undefined_arg const &) = delete;
         undefined_arg& operator= (undefined_arg const &) = delete;
         undefined_arg& operator= (undefined_arg &&) = delete;
         undefined_arg& operator= (undefined_arg const &&) = delete;
         undefined_arg(undefined_arg const &&) = delete;
         undefined_arg(undefined_arg &&) = delete;
   };

}

#endif //PQS_UNDEFINED_ARG_HPP_INCLUDED
