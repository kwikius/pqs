#ifndef PQS_SI_ACCELERATION_HPP_INCLUDED
#define PQS_SI_ACCELERATION_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/acceleration_unit.hpp>

namespace pqs{ namespace si { namespace acceleration{

   template <typename ValueType = double>
   using m_per_s2 = pqs::basic_quantity<pqs::si::acceleration_unit::m_per_s2,ValueType>;

}}} // pqs::si::acceleration

#endif // PQS_SI_ACCELERATION_HPP_INCLUDED
