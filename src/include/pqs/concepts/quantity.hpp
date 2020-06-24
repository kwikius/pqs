#ifndef PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};

      template <typename T, typename Where = void>
      struct get_unit_impl : pqs::undefined{};

      template <typename T, typename Where = void>
      struct get_numeric_type_impl : pqs::undefined{};

   }// impl

   template <typename T>
   struct is_quantity_legacy : impl::is_quantity_impl<typename pqs::meta::strip_cr<T>::type>{};

   template <typename T>
   struct get_unit_legacy {
      typedef typename impl::get_unit_impl<typename pqs::meta::strip_cr<T>::type>::type type;
      static_assert(pqs::is_defined_legacy<type>::value,"");
   };

   template <typename T>
   struct get_numeric_type_legacy {
      typedef typename impl::get_numeric_type_impl<typename pqs::meta::strip_cr<T>::type>::type type;
      static_assert(pqs::is_defined_legacy<type>::value,"");
   };

   template <typename T>
   using get_unit = typename get_unit_legacy<T>::type;

   template <typename T>
   using get_numeric_type = typename get_numeric_type_legacy<T>::type;

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
