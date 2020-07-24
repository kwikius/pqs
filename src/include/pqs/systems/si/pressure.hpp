#ifndef PQS_SI_PRESSURE_HPP_INCLUDED
#define PQS_SI_PRESSURE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/pressure_unit.hpp>

namespace pqs{ namespace si { namespace pressure{

   template <typename ValueType = double>
   using Pa = pqs::basic_quantity<pqs::si::pressure_unit::Pa,ValueType>;

}}} // pqs::si::pressure

#endif // PQS_SI_PRESSURE_HPP_INCLUDED
