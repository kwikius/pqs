#ifndef PQS_SI_UNITS_SUBSTANCE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_SUBSTANCE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/base_quantity/substance.hpp>

/**
   si::quantity substance_unit definition namespace 
*/
namespace pqs::si::substance_unit{

   /**
    * @brief local derivation from base unit
    */

   struct mol : si::base_unit<base_substance>{};

} // pqs::si::substance_unit

#endif //PQS_SI_UNITS_SUBSTANCE_UNIT_HPP_INCLUDED
