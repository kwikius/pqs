#ifndef PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_dimensionless_quantity_impl : std::false_type{};

      template <typename T>
      struct is_dimensionless_quantity_impl< 
         T, typename pqs::where_<std::is_arithmetic<T> >::type
      > : std::true_type{};

   }

   template <typename T>
   struct is_dimensionless_quantity_legacy
   : impl::is_dimensionless_quantity_impl<
      typename pqs::meta::strip_cr<T>::type
   >{};

#if defined  __cpp_inline_variables

   template <typename T>
   constexpr inline bool is_dimensionless_quantity = is_dimensionless_quantity_legacy<T>::value;

   #if defined __cpp_concepts 

   template <typename T>
   concept dimensionless_quantity = is_dimensionless_quantity<T>;

   #endif

#endif


} //pqs

#endif // PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
