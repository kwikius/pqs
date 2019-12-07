#ifndef PQS_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_QUANTITIES_LENGTH_HPP_INCLUDED

#include <pqs/bits/quantity.hpp>
#include <pqs/units/length_unit.hpp>

// si quantities length definition namespace 
namespace pqs{ namespace length{

   template <typename ValueType = double>
   using mm = quantity<length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = quantity<length_unit::ft,ValueType>;

}} // pqs::length

#endif // PQS_QUANTITIES_LENGTH_HPP_INCLUDED
