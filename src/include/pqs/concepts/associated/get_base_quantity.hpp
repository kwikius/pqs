#ifndef PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>
#include <type_traits>

namespace pqs{

   namespace impl{

     /**
      *  @brief get base_quantity from a base_quantity_exponent - impl default
      */
      template <typename T>
      struct get_base_quantity_impl : pqs::undefined{};
   }

     /**
      *  @brief get base_quantity from a base_quantity_exponent - interface
      */
   template <typename T>
   using get_base_quantity = typename impl::get_base_quantity_impl<
      std::remove_cvref_t<T>
   >::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_BASE_QUANTITY_HPP_INCLUDED
