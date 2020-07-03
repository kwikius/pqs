#ifndef PQS_IMPERIAL_LENGTH_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_HPP_INCLUDED

#include <pqs/instance/basic_quantity.hpp>
#include <pqs/imperial/units/length_unit.hpp>

namespace pqs{ namespace imperial { namespace length{

   template <typename ValueType = double>
   using ft = pqs::basic_quantity<pqs::imperial::length_unit::ft,ValueType>;

   template <typename ValueType = double>
   using yd = pqs::basic_quantity<pqs::imperial::length_unit::yd,ValueType>;

   template <typename ValueType = double>
   using mi = pqs::basic_quantity<pqs::imperial::length_unit::mi,ValueType>;

}}} // pqs::imperial::length

#endif // PQS_SI_LENGTH_HPP_INCLUDED
