#ifndef PQS_SYSTEMS_SI_AREA_HPP_INCLUDED
#define PQS_SYSTEMS_SI_AREA_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/area_unit.hpp>

/**
 *  si::quantity area definition namespace 
 */
namespace pqs::si::area{

   template <typename ValueType = double>
   using m2 = basic_quantity<area_unit::m2,ValueType>;

   template <typename ValueType = double>
   using mm2 = basic_quantity<area_unit::mm2,ValueType>;

   template <typename ValueType = double>
   using cm2 = basic_quantity<area_unit::cm2,ValueType>;

} // pqs::si::area

#endif // PQS_SYSTEMS_SI_AREA_HPP_INCLUDED
