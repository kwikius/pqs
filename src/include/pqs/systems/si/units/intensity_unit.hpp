#ifndef PQS_SI_UNITS_INTENSITY_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_INTENSITY_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/base_quantity/intensity.hpp>

/**
   si::quantity intensity_unit definition namespace 
*/
namespace pqs::si::intensity_unit{

   /**
    * @brief local derivation from base unit
    */

   struct cd : si::base_unit<base_intensity>{};

} // pqs::si::intensity_unit

#endif //PQS_SI_UNITS_INTENSITY_UNIT_HPP_INCLUDED
