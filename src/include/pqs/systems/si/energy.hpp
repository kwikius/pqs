#ifndef PQS_SYSTEMS_SI_ENERGY_HPP_INCLUDED
#define PQS_SYSTEMS_SI_ENERGY_HPP_INCLUDED

#include <pqs/systems/si/units/energy_unit.hpp>

namespace pqs::si::energy{

   template <typename ValueType = double>
   using J = pqs::basic_quantity<pqs::si::energy_unit::J,ValueType>;

   template <typename ValueType = double>
   using mJ = pqs::basic_quantity<pqs::si::energy_unit::mJ,ValueType>;

   template <typename ValueType = double>
   using kJ = pqs::basic_quantity<pqs::si::energy_unit::kJ,ValueType>;

} //pqs::si::energy

#endif // PQS_SYSTEMS_SI_ENERGY_HPP_INCLUDED
