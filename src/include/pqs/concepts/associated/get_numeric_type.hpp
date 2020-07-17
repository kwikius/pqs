#ifndef PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED

namespace pqs{

   namespace impl{
      template <typename T, typename Where = void>
      struct get_numeric_type_impl : pqs::undefined{};
   }

   template <typename T>
   struct get_numeric_type_legacy  : impl::get_numeric_type_impl< std::remove_cvref_t<T> >{};

   template <typename T>
   using get_numeric_type = typename get_numeric_type_legacy<T>::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
