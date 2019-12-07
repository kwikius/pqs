#ifndef PQS_SI_LENGTH_HPP_INCLUDED
#define PQS_SI_LENGTH_HPP_INCLUDED

#include <pqs/quantity.hpp>
#include <pqs/si/length_unit.hpp>

// si quantities length definition namespace 
namespace pqs{ namespace si { namespace length{

   template <typename ValueType = double>
   using mm = quantity<length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = quantity<length_unit::ft,ValueType>;

}}} // std::si::length

#endif // PQS_SI_LENGTH_HPP_INCLUDED
