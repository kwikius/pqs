#ifndef PQS_SI_MOMENTUM_HPP_INCLUDED
#define PQS_SI_MOMENTUM_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/momentum_unit.hpp>

namespace pqs{ namespace si { namespace momentum{

   template <typename ValueType = double>
   using kg_m_per_s = pqs::basic_quantity<pqs::si::momentum_unit::kg_m_per_s,ValueType>;

}}} // pqs::si::momentum

#endif // PQS_SI_MOMENTUM_HPP_INCLUDED
