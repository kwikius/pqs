#ifndef PQS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_BASE_QUANTITY_HPP_INCLUDED

#include <pqs/bits/universally_unique_id.hpp>
#include <pqs/concepts/base_quantity.hpp>

namespace pqs{

   namespace detail{
      struct base_quantity_base_class{};
   }

   template <typename Id>
   struct base_quantity : pqs::detail::base_quantity_base_class{
      typedef Id identifier;
      typedef base_quantity type;
   };

}//pqs

#endif // PQS_BASE_QUANTITY_HPP_INCLUDED
