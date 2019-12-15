#ifndef PQS_EXPOSITION_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_EXPOSITION_QUANTITIES_LENGTH_HPP_INCLUDED

#include <pqs/bits/quantity.hpp>
#include <pqs/exposition/units/length_unit.hpp>

// si quantities length definition namespace 
namespace pqs_exposition{ namespace length{

   template <typename ValueType = double>
   using mm = pqs::quantity<pqs_exposition::length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = pqs::quantity<pqs_exposition::length_unit::ft,ValueType>;

}} // pqs::length

#endif // PQS_EXPOSITION_QUANTITIES_LENGTH_HPP_INCLUDED
