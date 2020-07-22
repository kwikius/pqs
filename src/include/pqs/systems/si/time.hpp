#ifndef PQS_SI_TIME_HPP_INCLUDED
#define PQS_SI_TIME_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/time_unit.hpp>

// si quantities time definition namespace 
namespace pqs{ namespace si { namespace time{

   template <typename ValueType = double>
   using s = pqs::basic_quantity<pqs::si::time_unit::s,ValueType>;

   template <typename ValueType = double>
   using ms = pqs::basic_quantity<pqs::si::time_unit::ms,ValueType>;

   template <typename ValueType = double>
   using min = pqs::basic_quantity<pqs::si::time_unit::min,ValueType>;

}}} // pqs::si::time

#endif // PQS_SI_TIME_HPP_INCLUDED
