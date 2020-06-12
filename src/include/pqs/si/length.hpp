#ifndef PQS_SI_LENGTH_HPP_INCLUDED
#define PQS_SI_LENGTH_HPP_INCLUDED

#include <pqs/bits/quantity.hpp>
#include <pqs/si/units/length_unit.hpp>

// si quantities length definition namespace 
namespace pqs{ namespace length{

   template <typename ValueType = double>
   using mm = pqs::quantity<pqs::si::length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = pqs::quantity<pqs::si::length_unit::ft,ValueType>;

}} // pqs::length

#endif // PQS_SI_LENGTH_HPP_INCLUDED
