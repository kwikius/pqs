#ifndef PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/type_functions/get_unit.hpp>
#include <pqs/type_functions/get_dimension.hpp>
#include <pqs/type_functions/get_numeric_type.hpp>
#include <pqs/type_functions/get_conversion_factor.hpp>
#include <pqs/type_functions/get_measurement_system.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};

   }// impl

   template <typename T>
   struct is_quantity_legacy : impl::is_quantity_impl<typename pqs::meta::strip_cr<T>::type>{};

   template <typename T>
   inline constexpr bool is_quantity = is_quantity_legacy<T>::value;

   template <typename T>
   concept quantity = is_quantity<T>;


   namespace impl{

      template <quantity Q>
      struct get_dimension_impl<Q> : get_dimension<get_unit<Q> >{};

      template <quantity Q>
      struct get_conversion_factor_impl<Q> : get_conversion_factor<get_unit<Q> >{};

      template <quantity Q>
      struct get_measurement_system_impl<Q> : get_measurement_system<get_unit<Q> >{};

   }

}// pqs

#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
