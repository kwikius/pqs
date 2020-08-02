
#include <pqs/types/conversion_factor.hpp>

#include <iostream>
#include <iomanip>

/*
  pi as a conversion factor from pqs Wiki
*/

int main()
{
   std::cout << "PQS - pi as a conversion factor from pqs Wiki\n";

   using namespace pqs;

   auto constexpr pi = std::ratio<314159265358979>() ^ exponent10<-14>();
   static_assert(is_conversion_factor<decltype(pi)> );

   auto constexpr v1 = evaluate(pi);             // object argument form

   std::cout << std::setprecision(16) << "pi = " << v1 << '\n';
}