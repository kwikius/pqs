
#include "test.hpp"
#include <pqs/bits/scaled_value.hpp>
#include <iostream>

namespace {

   void conversion_factor_test1()
   {
      typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  
      typedef pqs::conversion_factor<std::ratio<1,7>,std::ratio<0> > cf_to;

      constexpr pqs::scaled_value<cf_from,double> sv{30.0};

      pqs::scaled_value<cf_to,double> sv1 = sv ;

      // v = sv1.v * 1
      // v = sv2.v * 1./7 
      // sv2.v * 1./7 = sv1.v
      // sv2.v = sv1.v * 7 
      // sv2.v = 30.0 * 7 
      // sv2.v = 210.0
      QUAN_CHECK((sv1.numeric_value() == 210.0))
   }

   void conversion_factor_test2()
   {
      typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  
      typedef pqs::conversion_factor<std::ratio<1,7>,std::ratio<2> > cf_to;

      constexpr pqs::scaled_value<cf_from,double> sv{30.0};

      pqs::scaled_value<cf_to,double> sv1 = sv ;

      // v = sv1.v * 1
      // v = sv2.v * 1./7 * 10^2
      // sv2.v * 1./7 *10^2 = sv1.v
      // sv2.v = sv1.v * 7 /100
      // sv2.v = 30.0 * 7 /100
      // sv2.v = 210.0 /100
      // sv2.v = 2.1
      QUAN_CHECK((sv1.numeric_value() == 2.1))
   }

   void conversion_factor_test3()
   {
      typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  
      typedef pqs::conversion_factor<std::ratio<1,7>,std::ratio<-2> > cf_to;

      constexpr pqs::scaled_value<cf_from,double> sv{30.0};

      pqs::scaled_value<cf_to,double> sv1 = sv ;

      // v = sv1.v * 1
      // v = sv2.v * 1./7 * 10^2
      // sv2.v * 1./7 *10^-2 = sv1.v
      // sv2.v = sv1.v * 7 *100
      // sv2.v = 30.0 * 7 *100
      // sv2.v = 210.0 *100
      // sv2.v = 21000
      QUAN_CHECK((sv1.numeric_value() == 21000))
   }

}

void scaled_value_test()
{
   conversion_factor_test1();
   conversion_factor_test2();
   conversion_factor_test3();
}