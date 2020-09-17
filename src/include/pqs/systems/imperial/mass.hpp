#ifndef PQS_SYSTEMS_IMPERIAL_MASS_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_MASS_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/mass_unit.hpp>
#include <pqs/systems/imperial/quantity/quantity_macro.hpp>

namespace pqs::imperial{

   PQS_IMPERIAL_QUANTITY_LITERAL(mass,lb)
   PQS_IMPERIAL_QUANTITY_LITERAL(mass,kg)

}

#endif //PQS_SYSTEMS_IMPERIAL_MASS_HPP_INCLUDED
