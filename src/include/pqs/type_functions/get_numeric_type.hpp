#ifndef PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
#define PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED

namespace pqs{

   namespace impl{
      template <typename T, typename Where = void>
      struct get_numeric_type_impl : pqs::undefined{};
   }

   template <typename T>
   struct get_numeric_type_legacy {
      typedef typename impl::get_numeric_type_impl<typename pqs::meta::strip_cr<T>::type>::type type;
     // static_assert(pqs::is_defined_legacy<type>::value,"");
   };

   template <typename T>
   using get_numeric_type = typename get_numeric_type_legacy<T>::type;
}

#endif // PQS_TYPE_FUNCTIONS_GET_NUMERIC_TYPE_HPP_INCLUDED
