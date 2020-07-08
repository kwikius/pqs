#ifndef PQS_SI_UNIT_HPP_INCLUDED1
#define PQS_SI_UNIT_HPP_INCLUDED1

#include <type_traits>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/si/measurement_system_def.hpp>

namespace pqs{ namespace si{

      namespace detail{
         struct si_unit_base{};
      }

      template <
         dimension D, 
         typename Exp = exponent10<0> 
      >
      struct unit : pqs::si::detail::si_unit_base{
         using dimension = std::remove_cvref_t<D>;
         using exponent = std::remove_cvref_t<Exp>;
         using type = unit;
      };

      namespace impl{

         template <typename U>
         struct is_si_unit_impl 
         :  std::is_base_of<
               pqs::si::detail::si_unit_base,
               U
            >{};

         template <pqs::unit U>
         struct make_si_unit_impl 
         : pqs::si::unit< 
            pqs::get_dimension<U>,
            typename pqs::get_conversion_factor<
               U
            >::exponent
         >{};
      }

      template <typename  U>
      constexpr inline bool is_si_unit = 
      pqs::si::impl::is_si_unit_impl<
         std::remove_cvref_t<U> 
      >::value;

      template <typename  U>
      using make_si_unit = 
      typename impl::make_si_unit_impl<
         std::remove_cvref_t<U>
      >::type;
   
   } // si

   namespace impl{

      template <typename U>
         requires pqs::si::is_si_unit<U>
      struct is_unit_impl<U> : std::true_type{};

      template <typename U>
         requires pqs::si::is_si_unit<U>
      struct get_measurement_system_impl<U>{
         using type = pqs::si_measurement_system;
      };

      template <typename U>
         requires pqs::si::is_si_unit<U>
      struct get_conversion_factor_impl<U> {
         using type = pqs::conversion_factor<
            std::ratio<1>,
            typename U::exponent
         >;
      };

      template <typename U>
         requires pqs::si::is_si_unit<U>
      struct get_dimension_impl<U>{
         using type = typename U::dimension;
      };
   }

namespace si{

   template <
      dimension D, 
      typename ConversionFactor
   >
   struct unit_conversion : pqs::basic_unit<
      pqs::si_measurement_system, 
      D, 
      ConversionFactor
   >{
      using type = unit_conversion;
   };

}}// pqs::si


#endif // PQS_SI_UNIT_HPP_INCLUDED
