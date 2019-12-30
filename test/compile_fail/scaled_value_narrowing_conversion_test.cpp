
#include <type_traits>
#include <pqs/bits/scaled_value.hpp>

#include <iostream>

int main()
{

   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  
   typedef pqs::conversion_factor<std::ratio<1,7>,std::ratio<0> > cf_to;

   constexpr pqs::scaled_value<double,cf_from> sv{30.0};

// ok
   pqs::scaled_value<int8_t,cf_to> sv1{sv, pqs::warn_narrowing_conversion{}};

// ok
   pqs::scaled_value<int8_t,cf_to> sv2{sv, pqs::saturating_conversion{}};

//##############################################
 // compile fail due to default conversion type of no_narrowing conversion
   pqs::scaled_value<int8_t,cf_to> sv3 = sv;
//###############################################

   return 0;
}