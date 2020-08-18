
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/acceleration.hpp>
#include <pqs/systems/si/density.hpp>
#include <pqs/systems/si/area.hpp>
#include <pqs/systems/si/power.hpp>

/*
* @brief calculate output power of a fountain
*/

using namespace pqs::si;
using namespace pqs::si::literals;

namespace {
   auto constexpr pi = 3.14159;
   auto constexpr g = 9.8q_m_per_s2;
   auto constexpr water_density = 1000.0q_kg_per_m3;
}

int main()
{
   /**
   *  @brief  height of fountain spray
   */
   auto constexpr spray_height = 0.6q_m;
   auto constexpr nozzle_radius = 0.5q_mm; 
   auto constexpr num_nozzles = 12;

   /**
   *  @brief velocity of water exiting nozzle to achive fountain height
   * use v^2 = u^2 + 2 as
   */
   auto constexpr nozzle_velocity = pqs::pow<1,2>(2 * g * spray_height);

   /**
   *  @brief so volume of water per s from nozzles
   */
   auto constexpr volume_per_s = pi * pqs::pow<2,1>(nozzle_radius) * nozzle_velocity * num_nozzles;

   /**
   *  @brief so mass per s
   */
   auto constexpr mass_per_s =  volume_per_s * water_density;

   /**
   *  @brief so power = Force * distance / time ; force = mass * g , 
   */
   power::W<> constexpr power = mass_per_s * g * spray_height;

   std::cout << "fountain output power = " << power <<'\n';
}

