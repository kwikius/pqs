#ifndef PQS_CONCEPTS_UNIT_HPP_INCLUDED
#define PQS_CONCEPTS_UNIT_HPP_INCLUDED

// pqs::unit concept

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/type_functions/get_measurement_system.hpp>
#include <pqs/type_functions/get_dimension.hpp>
#include <pqs/type_functions/get_conversion_factor.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_unit_impl : std::false_type{};

   }

   template < typename  T>
   struct is_unit_legacy : impl::is_unit_impl<typename pqs::meta::strip_cr<T>::type>{};

#if defined  __cpp_inline_variables

   template <typename T>
   inline constexpr bool is_unit = is_unit_legacy<T>::value;

   #if defined __cpp_concepts

   template <typename T>
   concept unit = is_unit<T>;

   #endif

#endif

};


#endif // PQS_CONCEPTS_UNIT_HPP_INCLUDED
