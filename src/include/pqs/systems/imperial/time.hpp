#ifndef PQS_SYSTEMS_IMPERIAL_TIME_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_TIME_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/time_unit.hpp>
#include <pqs/systems/imperial/quantity/quantity_macro.hpp>

namespace pqs::imperial{

   PQS_IMPERIAL_QUANTITY_LITERAL(time,s)
   PQS_IMPERIAL_QUANTITY_LITERAL(time,min)
   PQS_IMPERIAL_QUANTITY_LITERAL(time,hr)

} // pqs::imperial::time

#endif // PQS_SYSTEMS_IMPERIAL_TIME_HPP_INCLUDED
