#ifndef PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/dimension.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct get_dimension_impl : pqs::undefined{};
   }

   template <typename T>
   using get_dimension =
      impl::get_dimension_impl< 
         std::remove_cvref_t<T> 
   >::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_DIMENSION_HPP_INCLUDED
