#ifndef PQS_SYSTEMS_SI_CURRENT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_CURRENT_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/current_unit.hpp>

/**
   si::quantity current definition namespace
*/
namespace pqs::si{

   /**
      @brief Macro for typedefs in namespace current e.g si::current::mA<> x{}
      and literals using pqs::si::literals eg 1.0_q_m, 1_q_mm etc
   */
   PQS_SI_QUANTITY_LITERAL(current,A)
   PQS_SI_QUANTITY_LITERAL(current,mA)
   PQS_SI_QUANTITY_LITERAL(current,uA)
   PQS_SI_QUANTITY_LITERAL(current,nA)
   PQS_SI_QUANTITY_LITERAL(current,pA)
   PQS_SI_QUANTITY_LITERAL(current,fA)

} // pqs::si

#endif // PQS_SYSTEMS_SI_CURRENT_HPP_INCLUDED
