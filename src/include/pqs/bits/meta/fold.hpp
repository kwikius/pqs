#ifndef PQS_META_FOLD_HPP_INCLUDED
#define PQS_META_FOLD_HPP_INCLUDED
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
#include <pqs/bits/meta/identity.hpp>

namespace pqs{ namespace meta{

   namespace detail{

      template < typename Seq, typename Init, typename F>
      struct fold_i{
         typedef typename pqs::meta::front<Seq>::type element_type;
         typedef typename F::template apply<Init,element_type>::type output_type;
         typedef typename pqs::meta::pop_front<Seq>::type list_in_next;
         typedef typename pqs::meta::eval_if_c<
            (pqs::meta::get_num_elements<list_in_next>::value > 0),
            fold_i<list_in_next,output_type,F>,
            identity<output_type>
         >::type type;
           
      };

   }//pqs::meta::detail


   template < typename Seq, typename Init, typename F>
   struct fold{
      typedef typename pqs::meta::eval_if_c<
         (pqs::meta::get_num_elements<Seq>::value > 0),
         pqs::meta::detail::fold_i<Seq,Init,F>,
         identity<Init>
      > ::type type;
   };


}}// pqs::meta

#endif // PQS_META_FOLD_HPP_INCLUDED
