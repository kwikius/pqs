#ifndef PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>

namespace pqs{

   namespace impl{
      template <typename T>
      struct get_numeric_type_impl : pqs::undefined{};
   }

   template <typename T>
   using get_numeric_type = 
      impl::get_numeric_type_impl< 
         std::remove_cvref_t<T> 
      >::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
