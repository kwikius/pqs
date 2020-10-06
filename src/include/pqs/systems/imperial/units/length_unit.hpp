#ifndef PQS_SYSTEMS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/types/charset.hpp>
#include <pqs/systems/imperial/unit.hpp>
#include <pqs/types/base_quantity/length.hpp>
#include <pqs/bits/named.hpp>

namespace pqs::imperial::length_unit{

   struct ft : pqs::base_unit<
      base_length,imperial_measurement_system
   >{};

   struct in : named<"in">,
      decltype( ft() / std::ratio<12>() )
   {};

   struct yd : 
      decltype( ft() * std::ratio<3>() )
   {
     /**
      * @brief demonstrate alternative name customisation
      * for when the utf8 charset name is diferent
      */ 
      template <typename CharSet>
      static constexpr auto name = 
         std::is_same_v<CharSet,charset_utf8> 
            ? "\u04b7\u0503" 
            : "yd"; // default to ascii
   };

   /**
    * @brief Si meter is a unit conversion in this system.
    *
    * Expressing the si base units in term of imperial base units
    * can be used for converting a quantity between measurement systems    
    */
   struct m : named<"m"> ,
      decltype( ft() * std::ratio<1250,381>())
   {};

   struct mi : named<"mi">,
      decltype( yd() * std::ratio<1760>() ) 
   {};

} // pqs::si::length_unit


#endif // PQS_SYSTEMS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
