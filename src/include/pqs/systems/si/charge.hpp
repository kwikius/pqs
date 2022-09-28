#ifndef PQS_SYSTEMS_SI_CHARGE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_CHARGE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/charge_unit.hpp>

/**
   si::quantity charge definition namespace
*/
namespace pqs::si{

   /**
      @brief Macro for typedefs in namespace charge e.g si::charge::mA<> x{}
      and literals using pqs::si::literals eg 1.0_q_m, 1_q_mm etc
   */
   PQS_SI_QUANTITY_LITERAL(charge,C)
   PQS_SI_QUANTITY_LITERAL(charge,mC)

} // pqs::si

#endif // PQS_SYSTEMS_SI_CHARGE_HPP_INCLUDED
