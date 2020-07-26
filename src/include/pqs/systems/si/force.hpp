#ifndef PQS_SI_FORCE_HPP_INCLUDED
#define PQS_SI_FORCE_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/force_unit.hpp>

namespace pqs{ namespace si { namespace force{

   template <typename ValueType = double>
   using N = pqs::basic_quantity<pqs::si::force_unit::N,ValueType>;

   template <typename ValueType = double>
   using mN = pqs::basic_quantity<pqs::si::force_unit::mN,ValueType>;

   template <typename ValueType = double>
   using kN = pqs::basic_quantity<pqs::si::force_unit::kN,ValueType>;

  

}}} // pqs::si::speed

#endif // PQS_SI_FORCE_HPP_INCLUDED
