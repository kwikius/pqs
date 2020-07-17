#ifndef PQS_SI_LENGTH_HPP_INCLUDED
#define PQS_SI_LENGTH_HPP_INCLUDED

#include <pqs/systems/si/basic_si_quantity.hpp>
#include <pqs/systems/si/units/length_unit.hpp>

/**
   si::quantity length definition namespace 
*/
namespace pqs::si::length{

   template <typename ValueType = double>
   using m = basic_quantity<length_unit::m,ValueType>;

   template <typename ValueType = double>
   using mm = basic_quantity<length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = basic_quantity<length_unit::ft,ValueType>;

} // pqs::si::length

#endif // PQS_SI_LENGTH_HPP_INCLUDED
