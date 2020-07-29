#ifndef PQS_IMPERIAL_LENGTH_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/length_unit.hpp>

namespace pqs::imperial::length{

   template <typename ValueType = double>
   using ft = pqs::make_quantity<pqs::imperial::length_unit::ft,ValueType>;

   template <typename ValueType = double>
   using yd = pqs::make_quantity<pqs::imperial::length_unit::yd,ValueType>;

   template <typename ValueType = double>
   using mi = pqs::make_quantity<pqs::imperial::length_unit::mi,ValueType>;

} // pqs::imperial::length

#endif // PQS_IMPERIAL_LENGTH_HPP_INCLUDED
