#ifndef PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/unit.hpp>

namespace pqs{

   namespace impl{
      template <typename T, typename Where = void>
      struct get_unit_impl : pqs::undefined{};
   }

   template <typename T>
   struct get_unit_legacy {
      typedef typename impl::get_unit_impl<typename pqs::meta::strip_cr<T>::type>::type type;
      static_assert(pqs::is_defined_legacy<type>::value,"");
   };

   template <typename T>
   using get_unit = typename get_unit_legacy<T>::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED
