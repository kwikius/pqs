#ifndef PQS_IMPERIAL_TIME_HPP_INCLUDED
#define PQS_IMPERIAL_TIME_HPP_INCLUDED

#include <pqs/types/basic_quantity.hpp>
#include <pqs/systems/imperial/units/time_unit.hpp>

namespace pqs{ namespace imperial { namespace time{

   template <typename ValueType = double>
   using s = pqs::basic_quantity<pqs::imperial::time_unit::s,ValueType>;

   template <typename ValueType = double>
   using min = pqs::basic_quantity<pqs::imperial::time_unit::min,ValueType>;

   template <typename ValueType = double>
   using hr = pqs::basic_quantity<pqs::imperial::time_unit::hr,ValueType>;

}}} // pqs::imperial::length

#endif // PQS_SI_TIME_HPP_INCLUDED
