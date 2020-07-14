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

      /**
        * @brief works out if a dimension and Exp10 exp combo is prefixable
        *  with an si prefix
      */
      template <dimension D , typename Exp> 
      inline constexpr bool is_prefixable()
      {
         using unit_exp = typename Exp::ratio;
         if constexpr ( is_base_quantity_exp<D> && (unit_exp::den == 1) ){
            using extent = get_exponent<D>;
            if constexpr ( 
               ( extent::den == 1 ) && 
               ( extent::num != 0 ) && 
               ( (unit_exp::num % extent::num) == 0) ){
                auto constexpr prefix = (unit_exp::num / extent::num) - 
                   get_base_unit_prefix_offset<get_base_quantity<D> >;
                return ( prefix == 0 ) || (unit_symbol_prefix<
                   static_cast<int>(prefix),charset_ascii
                > != basic_fixed_string("")); 
            } else {
               return false;
            }
         } else {
            return false;
         }
      }
       
      template <dimension D , typename Exp, typename CharSet> 
         requires is_prefixable<D,Exp>()
      inline constexpr 
      auto get_prefixed_unit_name()
      {
         using unit_exp = typename Exp::ratio;
         using extent = get_exponent<D>;
         using Qb = get_base_quantity<D>;

         auto constexpr prefix = (unit_exp::num / extent::num) - 
              get_base_unit_prefix_offset<Qb>;
         return unit_symbol_prefix<prefix,CharSet> + 
            get_unprefixed_base_unit_symbol<Qb,CharSet>;
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

      template <
         dimension D, 
         typename Exp
      >
         requires is_prefixable<D,Exp>()
      struct proper_unit<D,Exp> : pqs::si::impl::si_unit_base{

         using type = proper_unit;
         using quantity_system = si_measurement_system;
         using dimension = std::remove_cvref_t<D>;
         using conversion_factor = 
            pqs::conversion_factor<std::ratio<1>,Exp>;

         template <typename CharSet>
         static constexpr auto name = get_prefixed_unit_name<D,Exp,CharSet>();

      };

      template <base_quantity Qb>
      struct base_unit : proper_unit<
          typename make_base_quantity_exp<Qb,std::ratio<1> >::type,
          exponent10<0>
      >{
         using type = base_unit;
//         template <typename CharSet>
//         static constexpr auto name
//            = get_base_unit_symbol<Qb,si_measurement_system,CharSet>;
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

namespace pqs{

}


#endif // PQS_SI_UNIT_HPP_INCLUDED
