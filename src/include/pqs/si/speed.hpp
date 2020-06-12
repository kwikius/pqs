#ifndef PQS_SI_SPPED_HPP_INCLUDED
#define PQS_SI_SPEED_HPP_INCLUDED

#include <pqs/bits/quantity.hpp>
#include <pqs/si/units/speed_unit.hpp>

// si quantities speed definition namespace 
namespace pqs{ namespace speed{

   template <typename ValueType = double>
   using m_per_s = pqs::quantity<pqs::si::speed_unit::m_per_s,ValueType>;

}} // pqs::speed

#endif // PQS_SI_LENGTH_HPP_INCLUDED
