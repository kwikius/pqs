#ifndef PQS_CONCEPTS_UNIT_HPP_INCLUDED
#define PQS_CONCEPTS_UNIT_HPP_INCLUDED

// pqs::unit concept

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/type_functions/get_measurement_system.hpp>
#include <pqs/type_functions/get_dimension.hpp>
#include <pqs/type_functions/get_conversion_factor.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_unit_impl : std::false_type{};
   }

   template < typename  T>
   struct is_unit_legacy : impl::is_unit_impl< std::remove_cvref_t<T> >{};

   template <typename T>
   inline constexpr bool is_unit = is_unit_legacy<T>::value;

   template <typename T>
   concept unit = is_unit<T>;

    namespace impl{

      template <unit U>
      struct get_simple_dimension_impl<U> 
      : pqs::get_simple_dimension<pqs::get_dimension<U> >{};
    }
};

#endif // PQS_CONCEPTS_UNIT_HPP_INCLUDED
