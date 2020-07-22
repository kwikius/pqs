#ifndef PQS_SI_MASS_HPP_INCLUDED
#define PQS_SI_MASS_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/mass_unit.hpp>

/**
   si::quantity mass definition namespace 
*/
namespace pqs::si::mass{

   template <typename ValueType = double>
   using kg = basic_quantity<mass_unit::kg,ValueType>;

   template <typename ValueType = double>
   using g = basic_quantity<mass_unit::g,ValueType>;

} // pqs::si::mass

#endif // PQS_SI_MASS_HPP_INCLUDED
