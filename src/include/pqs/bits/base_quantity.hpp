#ifndef PQS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/universally_unique_id.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/bits/where.hpp>

namespace pqs{

   namespace detail{
      struct base_quantity_base_class{};
   }

   template <typename Id>
   struct base_quantity : pqs::detail::base_quantity_base_class{
      typedef Id identifier;
      typedef base_quantity type;
   };

   namespace impl{

      template <typename T>
      struct is_base_quantity_impl< 
         T,typename pqs::where_<std::is_base_of<pqs::detail::base_quantity_base_class,T> >::type
      > : std::true_type{};

   }

}//pqs

#endif // PQS_BASE_QUANTITY_HPP_INCLUDED
