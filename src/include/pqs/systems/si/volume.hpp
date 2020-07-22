#ifndef PQS_SI_VOLUME_HPP_INCLUDED
#define PQS_SI_VOLUME_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/volume_unit.hpp>

/**
 *  si::quantity volume definition namespace 
 */
namespace pqs::si::volume{

   template <typename ValueType = double>
   using m3 = basic_quantity<volume_unit::m3,ValueType>;

   template <typename ValueType = double>
   using mm3 = basic_quantity<volume_unit::mm3,ValueType>;

   template <typename ValueType = double>
   using cm3 = basic_quantity<volume_unit::cm3,ValueType>;

} // pqs::si::volume

#endif // PQS_SI_VOLUME_HPP_INCLUDED
