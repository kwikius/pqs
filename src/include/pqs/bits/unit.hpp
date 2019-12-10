#ifndef PQS_UNIT_HPP_INCLUDED
#define PQS_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/dimension.hpp>

namespace pqs{ 

   //interface
   template <typename Dim, int ExpN , int ExpD >
   struct unit_ratio{
      typedef Dim dimension;
      typedef typename std::ratio<ExpN,ExpD>::type exponent;
      typedef std::ratio<1,1> multiplier;
   };

   // derive named si_units from here
   template <typename Dim, int ExpN> 
   struct unit : unit_ratio<Dim, ExpN,1>{};

   // derive non_si_units from here
   template <typename SiUnit, int MuxExp, int MuxD>
   struct unit_conversion{
      typedef typename SiUnit::dimension dimension;
      typedef typename SiUnit::exponent exponent;
      typedef typename std::ratio<MuxExp,MuxD>::type multiplier;
   };

}// pqs

#endif // PQS_UNIT_HPP_INCLUDED
