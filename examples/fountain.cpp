
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/acceleration.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/density.hpp>
#include <pqs/systems/si/area.hpp>
#include <pqs/systems/si/volume.hpp>
#include <pqs/systems/si/speed.hpp>
#include <pqs/systems/si/power.hpp>

#include <pqs/concepts/associated/unit_binary_op.hpp>

/*
 * @brief calculate output power of a fountain
 * Demonstrates ad-hoc units for output
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

   std::cout << "PQS fountain power example\nDemo of ad-hoc output units\n";
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
   speed::m_per_s<> constexpr nozzle_velocity = pqs::pow<1,2>(2 * g * spray_height);

   /**
   *  @brief volume of water per s from nozzles
   */
   pqs::make_quantity< 
      decltype(volume_unit::cm3() / time_unit::s()) // ad-hoc cm3 per s unit
   > constexpr volume_per_s = 
      pi * pqs::pow<2,1>(nozzle_radius) * nozzle_velocity * num_nozzles;

   /**
   *  @brief mass per s from nozzles
   */
   pqs::make_quantity< 
      decltype(mass_unit::g() / time_unit::s()) // ad-hoc mass per s unit
   > constexpr mass_per_s = volume_per_s * water_density;

   /**
   *  @brief so power = Force * distance / time ; force = mass * g , 
   */
   power::W<> constexpr power = mass_per_s * g * spray_height;

   std::cout << "spray height = " << spray_height << "\n";
   std::cout << "volume per s = " << volume_per_s << "\n";
   std::cout << "mass per s = " << mass_per_s << "\n";

   std::cout << "fountain output power = " << power <<'\n';
}

