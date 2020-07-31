#ifndef PQS_SYSTEMS_SI_VOLTAGE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_VOLTAGE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/voltage_unit.hpp>

/**
   si::quantity voltage definition namespace 
*/
namespace pqs::si{
   
   /**
      @brief Macro for typedefs in namespace voltage 
   */
   PQS_SI_QUANTITY_LITERAL(voltage,V)
   PQS_SI_QUANTITY_LITERAL(voltage,mV)
   PQS_SI_QUANTITY_LITERAL(voltage,uV)
   PQS_SI_QUANTITY_LITERAL(voltage,nV)
   PQS_SI_QUANTITY_LITERAL(voltage,pV)
   PQS_SI_QUANTITY_LITERAL(voltage,fV)

} // pqs::si

#endif // PQS_SYSTEMS_SI_VOLTAGE_HPP_INCLUDED
