#ifndef PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
//#include <pqs/concepts/unit.hpp>

namespace pqs{

   namespace impl{
      template <typename T>
      struct get_unit_impl : pqs::undefined{};
   }

   template <typename T>
   using get_unit = 
      impl::get_unit_impl<
         std::remove_cvref_t<T>
      >::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_UNIT_HPP_INCLUDED
