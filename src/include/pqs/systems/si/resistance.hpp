#ifndef PQS_SYSTEMS_SI_RESISTANCE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_RESISTANCE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/resistance_unit.hpp>

/**
   si::quantity resistance definition namespace 
*/
namespace pqs::si{
   
   /**
      @brief Macro for typedefs in namespace resistance 
   */
   PQS_SI_QUANTITY_LITERAL(resistance,MR)
   PQS_SI_QUANTITY_LITERAL(resistance,kR)
   PQS_SI_QUANTITY_LITERAL(resistance,R)
   PQS_SI_QUANTITY_LITERAL(resistance,mR)

} // pqs::si

#endif // PQS_SYSTEMS_SI_RESISTANCE_HPP_INCLUDED
