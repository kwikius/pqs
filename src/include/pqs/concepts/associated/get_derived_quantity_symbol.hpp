#ifndef PQS_CONCEPTS_ASSOCIATED_GET_DERIVED_QUANTITY_SYMBOL_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_GET_DERIVED_QUANTITY_SYMBOL_HPP_INCLUDED

#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/measurement_system.hpp>
#include <pqs/types/fixed_string.hpp>

namespace pqs{

  /**
   * @brief a symbol for a dimension.
   * The symbol should be attached to a named_dimension( c++derived class 
   * of a simple dimension rather than a simple dimension, so that the 
   * dimensions with different names can be differentiated ( e.g torque and energy)
   *
   * NOTE : therefore named_dimension needs to be a C++ concept, then D below can be 
   * a model of named_dimension
,s o
   */
   template <
      dimension D,
      measurement_system S,
      typename CharSet
   > 
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol = "";

}

#endif // PQS_CONCEPTS_ASSOCIATED_GET_DERIVED_QUANTITY_SYMBOL_HPP_INCLUDED
