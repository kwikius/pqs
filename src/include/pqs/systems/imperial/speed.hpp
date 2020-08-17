#ifndef PQS_SYSTEMS_IMPERIAL_SPEED_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_SPEED_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/speed_unit.hpp>
#include <pqs/systems/imperial/quantity/quantity_macro.hpp>

namespace pqs::imperial{
   
   PQS_IMPERIAL_QUANTITY_LITERAL(speed,ft_per_s)
   PQS_IMPERIAL_QUANTITY_LITERAL(speed,yd_per_s)
   PQS_IMPERIAL_QUANTITY_LITERAL(speed,mi_per_hr)

}

#endif // PQS_SYSTEMS_IMPERIAL_SPEED_HPP_INCLUDED
