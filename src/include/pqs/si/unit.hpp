#ifndef PQS_SI_UNIT_HPP_INCLUDED1
#define PQS_SI_UNIT_HPP_INCLUDED1

#include <type_traits>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/si/measurement_system_def.hpp>

namespace pqs{ namespace si{

   /**
    * @brief derive si_unit_base from basic_unit_base
    *  to make si::proper_unit a model of pqs::unit
    */
      namespace impl{
         struct si_unit_base : pqs::impl::basic_unit_base{};
      }

      template <
         dimension D, 
         typename Exp = exponent10<0> 
      >
      struct proper_unit : pqs::si::impl::si_unit_base{

         using type = proper_unit;
         using quantity_system = si_measurement_system;
         using dimension = std::remove_cvref_t<D>;
         using conversion_factor = 
            pqs::conversion_factor<std::ratio<1>,Exp>;
      };

      template <base_quantity Qb>
      struct base_unit : proper_unit<
          typename make_base_quantity_exp<Qb,std::ratio<1> >::type,
          exponent10<0>
      >{
         template <typename CharSet>
         static constexpr auto symbol
            = get_base_unit_symbol<Qb,si_measurement_system,CharSet>;
      };

      namespace impl{

         template <typename U>
         struct is_proper_si_unit_impl 
         :  std::is_base_of<
               pqs::si::impl::si_unit_base,
               U
            >{};

         template <pqs::unit U>
         struct make_proper_si_unit_impl 
         : pqs::si::proper_unit< 
            pqs::get_dimension<U>,
            typename pqs::get_conversion_factor<
               U
            >::exponent
         >{};
      }

      template <typename  U>
      constexpr inline bool is_proper_si_unit = 
      pqs::si::impl::is_proper_si_unit_impl<
         std::remove_cvref_t<U> 
      >::value;

      template <typename  U>
      using make_proper_si_unit = 
      typename impl::make_proper_si_unit_impl<
         std::remove_cvref_t<U>
      >::type;
   
   } // si

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
