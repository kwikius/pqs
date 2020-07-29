#ifndef PQS_CONCEPTS_UNIT_HPP_INCLUDED
#define PQS_CONCEPTS_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/associated/unit_definition.hpp>
#include <pqs/concepts/associated/get_measurement_system.hpp>
#include <pqs/concepts/associated/get_dimension.hpp>
#include <pqs/concepts/associated/get_conversion_factor.hpp>

namespace pqs{

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
