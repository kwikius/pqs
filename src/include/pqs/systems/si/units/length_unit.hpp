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
   struct fm : si::normative_unit<abstract_length_t, exponent10<-15> >{};
   struct pm : si::normative_unit<abstract_length_t, exponent10<-12> >{};
   struct nm : si::normative_unit<abstract_length_t, exponent10<-9> >{};
   struct um : si::normative_unit<abstract_length_t, exponent10<-6> >{};
   struct mm : si::normative_unit<abstract_length_t, exponent10<-3> >{};
   struct cm : si::normative_unit<abstract_length_t, exponent10<-2> >{};
   struct dm : si::normative_unit<abstract_length_t, exponent10<-1> >{};
   struct km : si::normative_unit<abstract_length_t, exponent10< 3> >{};

   /**
    * @brief  length unit conversions from other measurement systems
    * can use NTTP conversion_factor
    *  Various options for ft
    *  Imperial, international
    * We select the international foot
    * https://en.wikipedia.org/wiki/Foot_(unit)#International_foot
    */
    
   struct ft : named<"ft"> ,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<381,125>() ^ exponent10<-1>() 
      >
   {};

   struct ft_us : named<"ft(U.S.)"> ,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<12000,3937>() ^ exponent10<-1>() 
      >
   {};

   // 6  ft
   struct fathom : named<"fathom">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         get_conversion_factor<ft>() * std::ratio<6>()
      >
   {};

   struct fathom_us : named<"fathom_us">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         get_conversion_factor<ft_us>() * std::ratio<6>()
      >
   {};

   struct AU : named<"AU">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<1495979,1000000>() ^ exponent10<11>()
      >
   {};

   struct ch : named<"ch">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<502921,250000>() ^ exponent10<1>()
      >
   {};

   struct in : named<"in">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         get_conversion_factor<ft>() / std::ratio<12>()
      >
   {};

   struct thou : named<"thou">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<127,50>() ^ exponent10<-5>()
      >
   {};

   struct mil : named<"mil">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         get_conversion_factor<thou>{}  // same as thou
      >
   {};

   struct l_y : named<"l.y.">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<946073,100000>() ^ exponent10<15>()
      >
   {};

   struct mi : named<"mi">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<25146,15625>() ^ exponent10<3>()
      >
   {};

   struct mi_us : named<"mi(us)">,
      pqs::si::unit_conversion<
          abstract_length_t,
          get_conversion_factor<ft_us>() * std::ratio<5280>() // 5280 us ft
      >
   {};

   struct mi_naut : named<"mi(naut)">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<463,250>() ^ exponent10<3>()
      >
   {};

   struct pc : named<"pc">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<1542839,500000>() ^ exponent10<16>()
      >
   {};

   struct pica_comp : named<"pica(comp)">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<4233333,1000000>() ^ exponent10<-3>()
      >
   {};

   struct pica_prn : named<"pica(prn)">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<2108759,500000>() ^ exponent10<-3>()
      >
   {};

   struct point_comp : named<"point(comp)">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<1763889,500000>() ^ exponent10<-4>()
      >
   {};

   struct point_prn : named<"point(prn)">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<1757299,500000>() ^ exponent10<-4>()
      >
   {};

   struct rd : named<"rd">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<502921,100000>() ^ exponent10<0>()
      >
   {};

   struct yd : named<"yd">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         get_conversion_factor<ft>() * std::ratio<3>()
      >
   {};

   struct angstrom : named<"angstrom">,
      pqs::si::unit_conversion< 
         abstract_length_t,
         std::ratio<1>() ^ exponent10<-10>()
      >
   {};

} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
