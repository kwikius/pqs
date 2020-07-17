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
   struct get_unit_legacy : impl::get_unit_impl< std::remove_cvref_t<T> >{};

   template <typename T>
   using get_unit = typename get_unit_legacy<T>::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED
