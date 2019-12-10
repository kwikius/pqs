

#include <quan_matters/test/test.hpp>

#include <pqs/meta/to_power.hpp>


void meta_to_power_test()
{

   QUAN_CHECK( (pqs::meta::to_power<10,0>::value == 1));
   QUAN_CHECK( (pqs::meta::to_power<10,1>::value == 10));
   QUAN_CHECK( (pqs::meta::to_power<10,2>::value == 100));

   QUAN_CHECK( (pqs::meta::to_power<2,12>::value == 4096));
   QUAN_CHECK( (pqs::meta::to_power<1,12>::value == 1));

}