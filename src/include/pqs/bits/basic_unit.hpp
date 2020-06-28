#ifndef PQS_BASIC_UNIT_HPP_INCLUDED
#define PQS_BASIC_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/unit.hpp>
#include <pqs/bits/where.hpp>

/**
 *  basic_unit : encapsulates quantity system, dimension and conversion factor
 *  but without the numeric value.
 */
namespace pqs{ 

   namespace detail{
      struct basic_unit_base{};
   }

   template <
      typename QuantitySystem,
      typename Dim, 
      typename ConversionFactor
   >
   struct basic_unit : pqs::detail::basic_unit_base{
      typedef QuantitySystem quantity_system;
      typedef Dim dimension;
      typedef ConversionFactor conversion_factor;
   };

   namespace impl{

      template <typename T> 
      struct is_basic_unit_impl : std::is_base_of<pqs::detail::basic_unit_base,T>{};
   }

   template <typename T> 
   struct is_basic_unit_legacy : pqs::impl::is_basic_unit_impl<typename pqs::meta::strip_cr<T>::type>{};

   template <typename T>
   inline constexpr bool is_basic_unit = is_basic_unit_legacy<T>::value;

   // implement unit concept requirements for basic unit
   
   namespace impl{

      template <typename T>
      struct get_measurement_system_impl<
          T, 
         typename pqs::where_<pqs::is_basic_unit_legacy<T> >::type
      >{
         using type = typename T::quantity_system;
      };

      template <typename T>
      struct get_conversion_factor_impl<
          T, 
         typename pqs::where_<pqs::is_basic_unit_legacy<T> >::type
      >{
         using type = typename T::conversion_factor;
      };

      template <typename T>
      struct get_dimension_impl<
          T, 
         typename pqs::where_<pqs::is_basic_unit_legacy<T> >::type
      >{
         using type = typename T::dimension;
      };

   }

}// pqs

#endif // PQS_BASIC_UNIT_HPP_INCLUDED
