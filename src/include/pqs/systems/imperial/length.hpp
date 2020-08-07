#ifndef PQS_IMPERIAL_LENGTH_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/length_unit.hpp>
#include <pqs/systems/imperial/quantity/quantity_macro.hpp>

namespace pqs::imperial{

   PQS_IMPERIAL_QUANTITY_LITERAL(length,in)
   PQS_IMPERIAL_QUANTITY_LITERAL(length,ft)
   PQS_IMPERIAL_QUANTITY_LITERAL(length,yd)
   PQS_IMPERIAL_QUANTITY_LITERAL(length,m)
   PQS_IMPERIAL_QUANTITY_LITERAL(length,mi)
}

#endif // PQS_IMPERIAL_LENGTH_HPP_INCLUDED
