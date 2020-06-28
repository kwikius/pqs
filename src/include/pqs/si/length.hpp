#ifndef PQS_SI_LENGTH_HPP_INCLUDED
#define PQS_SI_LENGTH_HPP_INCLUDED

#include <pqs/instance/basic_quantity.hpp>
#include <pqs/si/units/length_unit.hpp>

// si quantities length definition namespace 
namespace pqs{ namespace si { namespace length{

   template <typename ValueType = double>
   using mm = pqs::basic_quantity<pqs::si::length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = pqs::basic_quantity<pqs::si::length_unit::ft,ValueType>;

}}} // pqs::si::length

#endif // PQS_SI_LENGTH_HPP_INCLUDED
