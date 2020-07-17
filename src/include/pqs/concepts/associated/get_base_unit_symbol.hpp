#ifndef PQS_ASSOCIATED_GET_BASE_UNIT_SYMBOL_HPP_INCLUDED
#define PQS_ASSOCIATED_GET_BASE_UNIT_SYMBOL_HPP_INCLUDED

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/measurement_system.hpp>
#include <pqs/types/fixed_string.hpp>
#include <pqs/types/charset.hpp>

namespace pqs{

   /**
   *  @brief The I/O symbol for the base quantity Q
   *         as a base unit of system S in the Charset
   */
   template <
      base_quantity Qb,
      measurement_system S,
      typename CharSet
   > 
   inline constexpr 
   basic_fixed_string get_base_unit_symbol = "";

}

#endif // PQS_ASSOCIATED_GET_BASE_UNIT_SYMBOL_HPP_INCLUDED
