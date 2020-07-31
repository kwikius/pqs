#ifndef PQS_SI_UNIT_HPP_INCLUDED1
#define PQS_SI_UNIT_HPP_INCLUDED1

#include <type_traits>
#include <pqs/concepts/associated/make_unit.hpp>
#include <pqs/systems/si/quantity/measurement_system_def.hpp>
#include <pqs/systems/si/quantity/base_unit_symbols.hpp>
#include <pqs/systems/si/quantity/unit_symbol_prefix.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/concepts/associated/unit_binary_op.hpp>
#include <pqs/systems/si/quantity/quantity_macro.hpp>

namespace pqs::si{

      namespace impl{
         /**
          * @brief derive si_unit_base from basic_unit_base
          *  a detector base class to make si::normative_unit a model of pqs::unit
          */
         struct si_unit_base : pqs::impl::basic_unit_base{};
      }

     /**
      * @brief return true if Exp can be prefixed.
      * N.B doesnt take into account extent
      */
      template <typename Exp>
      inline constexpr bool is_prefixable_exponent()
      {
         using unit_exp = typename Exp::ratio;
         return (unit_exp::den == 1 ) && 
                ((unit_exp::num == 0 ) ||
                (unit_symbol_prefix<
                static_cast<int>(unit_exp::num),charset_ascii
             > != basic_fixed_string(""))); 
      }

     /**
      * @brief return true if D is a named dimension
      */
      template <dimension D>
      inline constexpr bool is_named_dimension()
      {
         return get_derived_quantity_symbol<
            D,si_measurement_system,charset_utf8
         > != basic_fixed_string("");
      }

     /**
      * @brief Is a dimension and exponent10 combo prefixable
      *  with an si prefix for base_quantity_exponents?
      */
      template <dimension D , typename Exp> 
      inline constexpr bool is_prefixable()
      {
         using unit_exp = typename Exp::ratio;
         if constexpr ( is_base_quantity_exponent<D> && (unit_exp::den == 1) ){
            using extent = get_exponent<D>;
            if constexpr ( 
               ( extent::den == 1 ) && 
               ( extent::num != 0 ) && 
               ( (unit_exp::num % extent::num) == 0) ){
                auto constexpr prefix = (unit_exp::num / extent::num) + 
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

      /**
       *  Get unit name + prefix of dimension, exponent10 combo, 
       *  where the combo is prefixable
       *  For base_dimension_exponents
       */       
      template <dimension D , typename Exp, typename CharSet> 
         requires is_prefixable<D,Exp>()
      inline constexpr 
      auto get_prefixed_unit_name()
      {
         using unit_exp = typename Exp::ratio;
         using extent = get_exponent<D>;
         using Qb = get_base_quantity<D>;

         auto constexpr prefix = (unit_exp::num / extent::num) + 
              get_base_unit_prefix_offset<Qb>;
         if constexpr ( extent::num ==1)
            return unit_symbol_prefix<prefix,CharSet> + 
               get_unprefixed_base_unit_symbol<Qb,CharSet>;
         else
            return unit_symbol_prefix<prefix,CharSet> + 
               get_unprefixed_base_unit_symbol<Qb,CharSet> +
                  detail::superscript_integer<
                     static_cast<int>(extent::num),CharSet
                  >;
      }
      
      /**
       *  @brief normative si unit, by default has no name
       */
      template <
         dimension D, 
         typename Exp = exponent10<0> 
      >
      struct normative_unit : pqs::si::impl::si_unit_base{

         using type = normative_unit;
         using quantity_system = si_measurement_system;
         using dimension = std::remove_cvref_t<D>;
         using conversion_factor = 
            pqs::conversion_factor<std::ratio<1>,Exp>;
      };

      /**
       *  @brief normative si unit, includes an automated member ::name 
       *  This version is from a base_dimension exponent
       *  so long as exp is prefixable
       */
      template <
         dimension D, 
         typename Exp
      >
         requires is_prefixable<D,Exp>()
      struct normative_unit<D,Exp> : pqs::si::impl::si_unit_base{

         using type = normative_unit;
         using quantity_system = si_measurement_system;
         using dimension = std::remove_cvref_t<D>;
         using conversion_factor = 
            pqs::conversion_factor<std::ratio<1>,Exp>;

         template <typename CharSet>
         static constexpr auto name = get_prefixed_unit_name<D,Exp,CharSet>();
      };

      namespace detail{
      
        /**
          * @brief Add prefix to named unit
         */
         template <dimension D, typename Exp, typename CharSet>
         inline auto constexpr 
         prefix_named_unit()
         {
            return unit_symbol_prefix<Exp::ratio::num,CharSet> +
               get_derived_quantity_symbol<D,si_measurement_system,CharSet>;
         }
      }

      /**
       *  @brief normative si unit, includes an automated member ::name 
       *  This version is from a named dimension aka derived quantity
       *  so long as the exp is prefixable
       */
      template <
         dimension D, 
         typename Exp
      >
         requires
            is_named_dimension<D>() &&
            is_prefixable_exponent<Exp>()
      struct normative_unit<D,Exp> : pqs::si::impl::si_unit_base{

         using type = normative_unit;
         using quantity_system = si_measurement_system;
         using dimension = std::remove_cvref_t<D>;
         using conversion_factor = 
            pqs::conversion_factor<std::ratio<1>,Exp>;

         template <typename CharSet>
         static constexpr auto name = detail::prefix_named_unit<D,Exp,CharSet>();
      };

      /**
        * @brief make a si base unit from a base_quantity
        */
      template <base_quantity Qb>
      struct base_unit : normative_unit<
          typename make_base_quantity_exp<Qb,std::ratio<1> >::type,
          exponent10<0>
      >{
         using type = base_unit;
      };

      namespace impl{

     /**
      * @brief is_normative_unit impl
      */
         template <typename U>
         struct is_normative_unit_impl 
         :  std::is_base_of<
               pqs::si::impl::si_unit_base,
               U
            >{};

     /**
      * @brief make_normative_unit impl
      */
         template <pqs::unit U>
         struct make_normative_unit_impl 
         : pqs::si::normative_unit< 
            pqs::get_dimension<U>,
            typename pqs::get_conversion_factor<
               U
            >::exponent
         >{};
      }

     /**
      * @brief is_normative_unit interface
      */
      template <typename  U>
      constexpr inline bool is_normative_unit = 
      pqs::si::impl::is_normative_unit_impl<
         std::remove_cvref_t<U> 
      >::value;

      template <quantity Q>
      constexpr inline bool is_normative_quantity( Q const & q)
      {
         return is_normative_unit<get_unit<Q> >;
      }

      namespace impl{

        /**
         * @brief A unit_binary_op is a normative unit 
         *        if both operands are
         */
         template <unit U>
            requires is_unit_binary_op<U>
         struct is_normative_unit_impl<
            U 
         > : std::bool_constant<
               is_normative_unit<typename U::lhs_unit> &&
               is_normative_unit<typename U::rhs_unit>
         >{};
      }

     /**
      * @brief make_normative_unit interface
      */
      template <typename  U>
      using make_normative_unit = 
      typename impl::make_normative_unit_impl<
         std::remove_cvref_t<U>
      >::type;
   
     /**
      * @brief non si units that can work with si units in the si system
      */
      template <
         dimension D, 
         conversion_factor CF
      >
      struct unit_conversion : pqs::make_unit<
         pqs::si_measurement_system, 
         D, 
         decltype(CF)
      >{
         using type = unit_conversion;
      };

}// pqs::si

#endif // PQS_SI_UNIT_HPP_INCLUDED
