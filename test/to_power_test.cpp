

#include "test.hpp"
#include <cmath>
#include <pqs/meta/to_power.hpp>
#include <pqs/math/root.hpp>
#include <iostream>

namespace{


   template <int N>
   constexpr void show_root(double const & v)
   {
      auto constexpr v0 = pqs::root<N>(100.0);
     auto v1 = pqs::root<N>(v);
    // std::cout << "pqs::root<" << N << ">( "<< v <<" ) = " << v1 <<'\n';
     auto v2 = std::pow(v, 1./N);
    // std::cout << "std::pow(" << v << ", 1./" << N << " = " << v2 <<'\n';
   }

   void fun()
   {

    show_root<2>(100.0);

    show_root<2>(2.0);

    show_root<3>(2.0);

    show_root<2>(3.0);

    show_root<3>(3.0);

   }
}


void meta_to_power_test()
{

   QUAN_CHECK( (pqs::meta::to_power<10,0>::value == 1));
   QUAN_CHECK( (pqs::meta::to_power<10,1>::value == 10));
   QUAN_CHECK( (pqs::meta::to_power<10,2>::value == 100));

   QUAN_CHECK( (pqs::meta::to_power<2,12>::value == 4096));
   QUAN_CHECK( (pqs::meta::to_power<1,12>::value == 1));

}

