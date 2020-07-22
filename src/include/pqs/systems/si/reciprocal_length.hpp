#ifndef PQS_SI_RECIPROCAL_LENGTH_HPP_INCLUDED
#define PQS_SI_RECIPROCAL_LENGTH_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/reciprocal_length_unit.hpp>

namespace pqs::si::reciprocal_length{

   template <typename ValueType = double>
   using per_m = basic_quantity<reciprocal_length_unit::per_m,ValueType>;

   template <typename ValueType = double>
   using per_mm = basic_quantity<reciprocal_length_unit::per_mm,ValueType>;

   template <typename ValueType = double>
   using per_cm = basic_quantity<reciprocal_length_unit::per_cm,ValueType>;

   template <typename ValueType = double>
   using per_km = basic_quantity<reciprocal_length_unit::per_km,ValueType>;
   
} // pqs::si::reciprocal_length

#endif // PQS_SI_RECIPROCAL_LENGTH_HPP_INCLUDED
