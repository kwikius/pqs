#ifndef PQS_BITS_DIMENSION_TO_FIXED_STRING_HPP_INCLUDED
#define PQS_BITS_DIMENSION_TO_FIXED_STRING_HPP_INCLUDED

#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/associated/get_base_unit_symbol.hpp>
#include <pqs/bits/fixed_string_charset_stuff.hpp>

namespace pqs{

   namespace detail {

     /**
      * @ brief encode a dimension to a fixed_string - impl
      */
      template <
         typename D,
         pqs::measurement_system Ms,
         typename CharSet
      >
      struct dimension_to_fixed_string_impl;
   }

   /**
    * @brief interface : output a dimension as a fixed_string - type form
    *
    */
   template < 
      pqs::dimension D, 
      pqs::measurement_system Ms, 
      typename CharSet
   >
   inline constexpr 
   auto dimension_to_fixed_string()
   {
      return detail::dimension_to_fixed_string_impl<
         std::remove_cvref_t<D>,Ms,CharSet
      >::apply();
   }

   /**
    * @brief interface : output a dimension as a fixed_string - object form
    */
   template < 
      pqs::measurement_system Ms, 
      typename CharSet,
      pqs::dimension D
   >
   inline constexpr 
   auto dimension_to_fixed_string(D)
   {
      return detail::dimension_to_fixed_string_impl<
         std::remove_cvref_t<D>,Ms,CharSet
      >::apply();
   }

   namespace detail {

      /**
       * @brief generic base_quantity_exponent 
       * to fixed_string impl
       */
      template <
         pqs::base_quantity_exponent Qbe,
         pqs::measurement_system Ms,
         typename CharSet
      >
      struct dimension_to_fixed_string_impl<
         Qbe,Ms,CharSet
      >{
         static constexpr auto apply()
         {
            using qB = pqs::get_base_quantity<Qbe>;
            using qE = pqs::get_exponent<Qbe>;

            auto constexpr no_ext_str = 
               pqs::get_base_unit_symbol<
                  qB,Ms,CharSet
               >;
            if constexpr ( std::ratio_equal_v<qE,std::ratio<1> > )
               return no_ext_str;
            else
               return no_ext_str + 
                  to_superscript_fixed_string<qE,CharSet>();      
         }
      };

      /**
       * @brief Single element dimension_list to fixed_string implementation
       * which terminates the dimensionlist dimension_to_fixed_string_impl recursion
      */
      template <pqs::base_quantity_exponent D,pqs::measurement_system Ms, typename CharSet>
      struct dimension_to_fixed_string_impl<
         pqs::dimension_list<D>,Ms,CharSet
      >{
         static constexpr auto apply()
         {   
            return dimension_to_fixed_string<
               D,Ms,CharSet
            >() ;   
         }
      };

      /**
       * @brief Multi element dimension_list to fixed_string implementation
       * https://www.nist.gov/pml/special-publication-811/nist-guide-si-chapter-6-rules-and-style-conventions-printing-and-using
      */
      template <
         pqs::base_quantity_exponent... D,
         pqs::measurement_system Ms, 
         typename CharSet
      >
      struct dimension_to_fixed_string_impl<
         pqs::dimension_list<D...>,Ms, CharSet
      >{
         static constexpr auto apply()
         {   
            using list = pqs::dimension_list<D...>;
            return dimension_to_fixed_string<
               pqs::meta::front_t<list>,
               Ms,
               CharSet
            >() + 
            multiplication_dot<CharSet> +
            dimension_to_fixed_string<
               pqs::meta::pop_front_t<list>,
               Ms, 
               CharSet
            >(); 
         }
      };

      /**
       * @brief Custom dimension to fixed_string implementation
      */
      template <typename D,pqs::measurement_system Ms,typename CharSet>
         requires pqs::is_custom_dimension<D>
      struct dimension_to_fixed_string_impl<
         D,Ms, CharSet
      >{
         static constexpr auto apply()
         {   
            return dimension_to_fixed_string<
               pqs::get_simple_dimension<D>,
               Ms,
               CharSet
            >();   
         }
      };

   }// detail

} // pqs

#endif // PQS_BITS_DIMENSION_TO_FIXED_STRING_HPP_INCLUDED
