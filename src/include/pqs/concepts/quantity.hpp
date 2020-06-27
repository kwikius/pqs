#ifndef PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/type_functions/get_unit.hpp>
#include <pqs/type_functions/get_numeric_type.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};

   }// impl

   template <typename T>
   struct is_quantity_legacy : impl::is_quantity_impl<typename pqs::meta::strip_cr<T>::type>{};

#if defined  __cpp_inline_variables

   template <typename T>
   inline constexpr bool is_quantity = is_quantity_legacy<T>::value;

   #if defined __cpp_concepts

   template <typename T>
   concept quantity = is_quantity<T>;

   #endif

#endif

}// pqs

#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
