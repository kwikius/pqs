#ifndef PQS_TYPE_FUNCTIONS_GET_SIMPLE_DIMENSION_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_SIMPLE_DIMENSION_HPP_INCLUDED


#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename D>
      struct get_simple_dimension_impl;
   }

   template <typename T>
   using get_simple_dimension = typename impl::get_simple_dimension_impl<
      typename std::remove_cvref_t<T> 
   >::type;

}

#endif // PQS_TYPE_FUNCTIONS_GET_SIMPLE_DIMENSION_HPP_INCLUDED
