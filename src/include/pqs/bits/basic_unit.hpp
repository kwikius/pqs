#ifndef PQS_BASIC_UNIT_HPP_INCLUDED
#define PQS_BASIC_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/unit.hpp>

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

#if defined  __cpp_inline_variables

   template <typename T>
   inline constexpr bool is_basic_unit = is_basic_unit_legacy<T>::value;

#endif

}// pqs

#endif // PQS_BASIC_UNIT_HPP_INCLUDED
