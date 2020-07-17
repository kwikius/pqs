#ifndef PQS_META_TRANSFORM_HPP_INCLUDED
#define PQS_META_TRANSFORM_HPP_INCLUDED
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

#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/bits/meta/eval_if.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template <typename ListIn, typename ListOut, typename F>
      struct transform_i {
         using element_type = pqs::meta::front_t<ListIn>;
         using output_element = typename F::template apply<element_type>::type;
         using list_in_next = pqs::meta::pop_front_t<ListIn>;
         using list_out = pqs::meta::push_back_t<ListOut,output_element>;
         using type = typename pqs::meta::eval_if_c<
            (pqs::meta::get_num_elements_v<list_in_next> > 0),
            transform_i<list_in_next,list_out,F>,
            list_out
         >::type;
      };
   }
   // ListOut usually an empty list of correct type
   template <typename ListIn, typename ListOut, typename F>
   struct transform {
      using type = typename pqs::meta::eval_if_c<
         (pqs::meta::get_num_elements_v<ListIn> > 0),
         pqs::meta::detail::transform_i<ListIn,ListOut,F>,
         ListOut
      >::type ;
   };

}}


#endif // PQS_META_TRANSFORM_HPP_INCLUDED
