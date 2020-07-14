#ifndef PQS_BITS_QUANTITY_TO_FIXED_STRING_HPP_INCLUDED
#define PQS_BITS_QUANTITY_TO_FIXED_STRING_HPP_INCLUDED

#include <pqs/bits/unit_to_fixed_string.hpp>
#include <pqs/concepts/quantity.hpp>

namespace pqs{

   template <quantity Q,typename CharSet>
   inline constexpr auto
   dimension_to_fixed_string()
   {
      return dimension_to_fixed_string<
         pqs::get_unit<Q>,
         CharSet
      >();  
   }

   template <typename CharSet, quantity Q>
     // requires is_unit_binary_op<get_unit<Q> >
   inline constexpr 
   auto unit_to_fixed_string(Q)
   {
      return unit_to_fixed_string<get_unit<Q>,CharSet>();
   }

   /*
    *  generic object form
    */
   template <typename CharSet, typename T>
   inline constexpr auto
   dimension_to_fixed_string(T)
   {
      return dimension_to_fixed_string<T,CharSet>();
   }
}

#endif // PQS_BITS_QUANTITY_TO_FIXED_STRING_HPP_INCLUDED
