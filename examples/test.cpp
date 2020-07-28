

#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/area.hpp>

using namespace pqs::si::literals;

int main()
{
   auto constexpr q1 = 1.0q_m;
   auto constexpr q2 = -1q_m;
   auto constexpr q3 = 1.0q_cm;
   auto constexpr q4 = -1q_cm;
   auto constexpr q5 = 1.0q_mm;
   auto constexpr q6 = -1q_mm;
   auto constexpr q7 = 1.0q_km;
   auto constexpr q8 = -1q_km;

   auto constexpr q10 = 1.0q_mm2;
}