#ifndef PQS_SI_TIME_HPP_INCLUDED
#define PQS_SI_TIME_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/time_unit.hpp>

// si quantities time definition namespace 
namespace pqs::si { 

   PQS_SI_QUANTITY_LITERAL(time,s)
   PQS_SI_QUANTITY_LITERAL(time,ms)
   PQS_SI_QUANTITY_LITERAL(time,us)
   PQS_SI_QUANTITY_LITERAL(time,ns)
   PQS_SI_QUANTITY_LITERAL(time,ps)
   PQS_SI_QUANTITY_LITERAL(time,min)
   PQS_SI_QUANTITY_LITERAL(time,hr)

} // pqs::si

#endif // PQS_SI_TIME_HPP_INCLUDED
