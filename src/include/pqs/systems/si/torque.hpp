#ifndef PQS_SYSTEMS_SI_TORQUE_HPP_INCLUDED
#define PQS_SYSTEMS_SI_TORQUE_HPP_INCLUDED

#include <pqs/systems/si/units/torque_unit.hpp>

namespace pqs::si::torque{

   template <typename ValueType = double>
   using N_m = pqs::basic_quantity<pqs::si::torque_unit::N_m,ValueType>;

   template <typename ValueType = double>
   using mN_m = pqs::basic_quantity<pqs::si::torque_unit::mN_m,ValueType>;

} //pqs::si::torque

#endif // PQS_SYSTEMS_SI_TORQUE_HPP_INCLUDED
