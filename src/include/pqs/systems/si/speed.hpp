#ifndef PQS_SI_SPEED_HPP_INCLUDED
#define PQS_SI_SPEED_HPP_INCLUDED

#include <pqs/systems/si/basic_si_quantity.hpp>
#include <pqs/systems/si/units/speed_unit.hpp>

namespace pqs{ namespace si { namespace speed{

   template <typename ValueType = double>
   using m_per_s = pqs::basic_quantity<pqs::si::speed_unit::m_per_s,ValueType>;

}}} // pqs::si::speed

#endif // PQS_SI_SPEED_HPP_INCLUDED
