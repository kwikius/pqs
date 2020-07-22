#ifndef PQS_SI_DENSITY_HPP_INCLUDED
#define PQS_SI_DENSITY_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/density_unit.hpp>

namespace pqs{ namespace si { namespace density{

   template <typename ValueType = double>
   using kg_per_m3 = pqs::basic_quantity<pqs::si::density_unit::kg_per_m3,ValueType>;

}}} // pqs::si::density

#endif // PQS_SI_DENSITY_HPP_INCLUDED
