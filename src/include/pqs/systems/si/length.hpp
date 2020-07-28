#ifndef PQS_SYSTEMS_SI_LENGTH_HPP_INCLUDED
#define PQS_SYSTEMS_SI_LENGTH_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/length_unit.hpp>

/**
   si::quantity length definition namespace 
*/
namespace pqs::si{
   
   /**
      @brief Macro for typedefs in namespace length e.g si::length::m<> x{}
      and literals using pqs::si::literals eg 1.0q_m, 1q_mm etc
   */
   PQS_SI_QUANTITY_LITERAL(length,m)
   PQS_SI_QUANTITY_LITERAL(length,mm)
   PQS_SI_QUANTITY_LITERAL(length,cm)
   PQS_SI_QUANTITY_LITERAL(length,km)
   PQS_SI_QUANTITY_LITERAL(length,ft)

} // pqs::si

#endif // PQS_SYSTEMS_SI_LENGTH_HPP_INCLUDED
