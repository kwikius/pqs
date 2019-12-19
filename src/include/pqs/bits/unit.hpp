#ifndef PQS_UNIT_HPP_INCLUDED
#define PQS_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/dimension.hpp>

namespace pqs{ 

   //interface
   template <typename Dim, int ExpN , int ExpD >
   struct unit_ratio{
      typedef Dim dimension;
      typedef typename std::ratio<ExpN,ExpD>::type exponent;
      typedef std::ratio<1,1> multiplier;
      typedef unit_ratio type;
   };

   template <typename BaseExp, int ExpN>
   struct base_unit : unit_ratio<dimension<BaseExp>,ExpN,1>{
      typedef base_unit type;
   };

   // derive named si_units from here
   template <typename Dim, int ExpN> 
   struct derived_unit : unit_ratio<Dim, ExpN,1>{ typedef derived_unit type;};

   template <typename Dim, int ExpN> 
   struct named_unit : unit_ratio<Dim, ExpN,1>{ typedef named_unit type;};

   template <int ExpN, typename ... Dims>
   struct unit : unit_ratio<dimension<Dims... >, ExpN,1>{ typedef unit type;};

   // derive non_si_units from here
   template <typename SiUnit, int MuxExp, int MuxD>
   struct unit_conversion{
      typedef typename SiUnit::dimension dimension;
      typedef typename SiUnit::exponent exponent;
      typedef typename std::ratio<MuxExp,MuxD>::type multiplier;
      typedef unit_conversion type;
   };

}// pqs

#endif // PQS_UNIT_HPP_INCLUDED
