#ifndef PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/base_quantity/length.hpp>
#include <pqs/bits/named.hpp>

/**
   si::quantity length_unit definition namespace 
*/
namespace pqs::si::length_unit{


   /**
    * @brief local derivation from base unit
    */
   struct m : si::base_unit<base_length>{};

   struct mm : si::normative_unit<abstract_length_t, exponent10<-3> >{};
   struct cm : si::normative_unit<abstract_length_t, exponent10<-2> >{};
   struct km : si::normative_unit<abstract_length_t, exponent10< 3> >{};

   /**
    * @brief  length unit conversions from other measurement systems
    * can use NTTP conversion_factor
    */
   template <conversion_factor CF>
   struct conversion : 
      pqs::si::unit_conversion<
         abstract_length_t,
         decltype(CF)
      >{};

   struct ft : named<"ft"> ,
      conversion< 
         std::ratio<381,125>() ^ exponent10<-1>() 
      >
   {};

} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
