#ifndef PQS_SYSTEMS_SI_FORCE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_FORCE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/force_unit.hpp>

namespace pqs:: si {

   PQS_SI_QUANTITY_LITERAL(force,N)
   PQS_SI_QUANTITY_LITERAL(force,mN)
   PQS_SI_QUANTITY_LITERAL(force,kN)
   PQS_SI_QUANTITY_LITERAL(force,uN)

// conversions ----------

   PQS_SI_QUANTITY_LITERAL(force,kgf)

} // pqs::si

#endif // PQS_SYSTEMS_SI_FORCE_HPP_INCLUDED
