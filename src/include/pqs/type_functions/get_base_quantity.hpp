#ifndef PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>
#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct get_base_quantity_impl : pqs::undefined{};

   }

   template <typename T>
   struct get_base_quantity_legacy : pqs::impl::get_base_quantity_impl<
      std::remove_cvref_t<T>
   >{};

   template <typename T>
   using get_base_quantity = typename get_base_quantity_legacy<T>::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED
