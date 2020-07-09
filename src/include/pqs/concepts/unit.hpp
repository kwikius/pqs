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

   template <typename T>
   inline constexpr bool is_unit = impl::is_unit_impl< 
      std::remove_cvref_t<T> 
   >::value;

   template <typename T>
   concept unit = is_unit<T>;

    namespace impl{

      template <unit U>
      struct get_simple_dimension_impl<U> 
      : get_simple_dimension<pqs::get_dimension<U> >{};
    }
   
   template < unit Uj,unit Uk> 
   inline constexpr bool same_measurement_system<Uj,Uk> = 
      same_measurement_system<
        get_measurement_system<Uj>,
        get_measurement_system<Uk> 
      >;

   template < unit Uj,unit Uk>
   inline constexpr bool dimensionally_equivalent<Uj,Uk> =
      dimensionally_equivalent<
         get_dimension<Uj>,
         get_dimension<Uk> 
      >;
};

#endif // PQS_CONCEPTS_UNIT_HPP_INCLUDED
