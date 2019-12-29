
#include <type_traits>
#include <pqs/bits/scaled_value.hpp>
#include <pqs/math/powerof10.hpp>
#include <pqs/bits/binary_op.hpp>

#include <iostream>

#if defined PQS_STANDALONE
int main()
#else
void sandbox()
#endif
{

   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  // m
   typedef pqs::conversion_factor<std::ratio<1>,std::ratio<-6> > cf_to;

   pqs::scaled_value<int,cf_from> sv{9};

   pqs::scaled_value<double,cf_to> sv1 = sv;

   std::cout << sv1.numeric_value() <<'\n';


   
}