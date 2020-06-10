#include "test.hpp"
#include <cmath>
#include <pqs/math/root.hpp>
#include <iostream>



namespace{


   template <int N>
   void show_root(double const & v)
   {
     auto v1 = pqs::root<N>(v);
     std::cout << "pqs::root<" << N << ">( "<< v <<" ) = " << v1 <<'\n';
     auto v2 = std::pow(v, 1./N);
     std::cout << "std::pow(" << v << ", 1./" << N << " = " << v2 <<'\n';
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

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{

fun();
#if defined PQS_STANDALONE
   EPILOGUE
#endif

}