

#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/moment_of_inertia.hpp>

using namespace pqs::si;
using namespace pqs::si::literals;
int main()
{
   moment_of_inertia::kg_s2<> v = 1._q_kg * pow<2,1>(1._q_m);

   std::cout << v << '\n';
}
