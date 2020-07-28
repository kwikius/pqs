

#include <pqs/systems/si/force.hpp>

using namespace pqs;

#include <iostream>

int main()
{
   std::cout << "PQS wiki example\n";

   si::force::kgf<> q1{1};
   si::force::mN<> q2 = q1;

   std::cout << q1 << " is a normative S.I. quantity = " << std::boolalpha << si::is_normative_quantity(q1) << '\n';
   std::cout << q2 << " is a normative S.I quantity = " << std::boolalpha << si::is_normative_quantity(q2) << '\n';
}