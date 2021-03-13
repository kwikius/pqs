#ifndef PQS_SYSTEMS_SI_INDUCTANCE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_INDUCTANCE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/inductance_unit.hpp>

/**
   si::quantity inductance definition namespace 
*/
namespace pqs::si{
   
   /**
      @brief Macro for typedefs in namespace inductance 
   */

   PQS_SI_QUANTITY_LITERAL(inductance,H)
   PQS_SI_QUANTITY_LITERAL(inductance,mH)
   PQS_SI_QUANTITY_LITERAL(inductance,uH)
   PQS_SI_QUANTITY_LITERAL(inductance,nH)

} // pqs::si

#endif // PQS_SYSTEMS_SI_INDUCTANCE_HPP_INCLUDED
