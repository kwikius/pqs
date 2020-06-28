#ifndef PQS_UNDEFINED_HPP_INCLUDED
#define PQS_UNDEFINED_HPP_INCLUDED

/*
 Copyright (c) 2019-2020 Andy Little 

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

#include <pqs/bits/is_undefined.hpp>

namespace pqs{ 

   struct undefined {
     
      typedef undefined type;

      private:
         undefined() = delete;
         undefined(undefined const &) = delete;
         undefined& operator= (undefined const &) = delete;
         undefined& operator= (undefined &&) = delete;
         undefined& operator= (undefined const &&) = delete;
         undefined(undefined const &&) = delete;
         undefined(undefined &&) = delete;
   };

   namespace impl{
 
      template  <>
      struct is_undefined_impl<pqs::undefined> : std::true_type{};

   }
}

#endif //PQS_UNDEFINED_HPP_INCLUDED

