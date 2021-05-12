
#include <pqs/systems/imperial/length.hpp>

namespace imp = pqs::imperial;


/*
 using pqs as a calculator. 
 The source makes a pleasing scripting language for simple calculations of this type
 with units expressed directly ( in my opinion!)
*/

int main()
{
   imp::length::ft<> q1{100};

   std::cout << "q1 = " << q1 <<'\n';

   auto q2 = pow<1,2>(q1);

   std::cout << "q2 ( square root of q1) =  " << q2 << '\n';

   imp::length::ft<> q3 = q2 * q2;

   std::cout << "q3 (q2^2 should be same as q1) = " << q3 << '\n';
}