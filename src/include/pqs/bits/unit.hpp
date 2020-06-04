#ifndef PQS_UNIT_HPP_INCLUDED
#define PQS_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/dimension.hpp>

/*
   unit : abstract_quantity with a dimension and conversion factor
    but without the numeric value.
   // do we want abstract_quantity? or dimension
   // abstract_quantity may be named or anonymous
   // so this would need the name for named
   // dimension is just the anonymous dimsneion part of the abstract_quantity
*/

namespace pqs{ 

   // unit_ratio_concept comprises dimension and rational si conversion factor exponent
   // the conversion factor is rational which diferentiates this from unit
   // rational si conversion factor will be rare in practise but can occur for instance
   // for sqrt(frequency) in some situations
   // Dim - a model of dimension_concept
   // Expn, Expd rational represenet in the conversion factor exponent
   // the conversion factor multiplier is implicitly 1
   // so this is a coherent quantity
   template <typename Dim, int ExpN , int ExpD >
   struct unit_ratio{
      typedef Dim dimension;
      typedef typename std::ratio<ExpN,ExpD>::type exponent;
      typedef std::ratio<1,1> multiplier;
      typedef unit_ratio type;
   };

   // raw dimension sequence used for quantity of multiple dimensions
   // Expn The conversion factors integer exponent
   // BaseExp a sequence of BaseExponents
   // essentially just a refinement of unit_ratio
   // most si units will be of this type
   template <int ExpN, typename ... BaseExp>
   struct unit : unit_ratio<base_quantity_exp_list<BaseExp... >, ExpN,1>{ typedef unit type;};

   // unit for base quantity eg length mass time area etc
   // BaseExp the base_quantity_exp_list exponent of the quantity
   // ExpN the integer exponent of the conversion factor
   template <typename BaseExp, int ExpN>
   struct base_unit : unit_ratio<base_quantity_exp_list<BaseExp>,ExpN,1>{
      typedef base_unit type;
   };

   // derive named si_units from here
   // differes from base_unit since Dim is a Dimension not a baseExp
   // ExpN  is the integer exponent of the conversion factor
   template <typename Dim, int ExpN> 
   struct derived_unit : unit_ratio<Dim, ExpN,1>{ typedef derived_unit type;};

   // named unit 
   template <typename Dim, int ExpN> 
   struct named_unit : unit_ratio<Dim, ExpN,1>{ typedef named_unit type;};

   // derive non_si_units from here
   // Si Unit is one of the above
   // incoherent unit
   template <typename SiUnit, int MuxExp, int MuxD>
   struct unit_conversion{
      typedef typename SiUnit::dimension dimension;
      typedef typename SiUnit::exponent exponent;
      typedef typename std::ratio<MuxExp,MuxD>::type multiplier;
      typedef unit_conversion type;
   };

}// pqs

#endif // PQS_UNIT_HPP_INCLUDED
