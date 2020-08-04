#ifndef PQS_CONCEPTS_QUANTITY_EXPLICIT_CAST_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_EXPLICIT_CAST_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>

namespace pqs{

   /**
    *  use for casting through narrowing conversion
   */
   template <dimensionless_quantity V, quantity Q>
   inline constexpr auto explicit_cast( Q const & q)
   {
      return make_quantity<get_unit<Q>,V>{
         static_cast<V>(get_numeric_value(q))
      };
   }
}

#endif // PQS_CONCEPTS_QUANTITY_EXPLICIT_CAST_HPP_INCLUDED
