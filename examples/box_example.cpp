
#include <pqs/systems/si/acceleration.hpp>
#include <pqs/systems/si/density.hpp>
#include <pqs/systems/si/force.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/volume.hpp>
#include <cassert>

using namespace pqs;
using namespace pqs::si::literals;

struct Box {
  static constexpr auto air_density = 1.225q_kg_per_m3;
  static constexpr auto g = 9.98q_m_per_s2;

  si::length::m<> length;
  si::length::m<> width;
  si::length::m<> height;

  struct {
    si::density::kg_per_m3<> density = air_density;
  } contents;

  constexpr Box(const si::length::m<>& l, const si::length::m<>& w, const si::length::m<>& h) : length{l}, width{w}, height{h} {}

  constexpr si::force::kN<> filled_weight() const
  {
    const si::volume::m3<> volume = length * width * height;
    const si::mass::kg<> mass = contents.density * volume;
    return mass * g;
  }

  constexpr si::length::m<> fill_level(const si::mass::kg<>& measured_mass) const
  {
    return height * (measured_mass * g) / filled_weight();
  }

  constexpr si::volume::m3<> spare_capacity(const si::mass::kg<>& measured_mass) const
  {
    return (height - fill_level(measured_mass)) * width * length;
  }

  constexpr void set_contents_density(const si::density::kg_per_m3<>& density_in)
  {
    assert(density_in > air_density);
    contents.density = density_in;
  }
};

#include <iostream>

int main()
{
  std::cout << "PQS box example\n";

  auto box = Box{1000.0q_mm, 500.0q_mm,200.0q_mm};
  box.set_contents_density(1000.0q_kg_per_m3);

  std::cout << "filled weight = " << box.filled_weight() <<'\n';

  const auto fill_time = 200.0q_s;      // time since starting fill
  const auto measured_mass = 20.0q_kg;  // measured mass at fill_time

  std::cout << "pqs box example...\n";
  std::cout << "fill height at " << fill_time << " = " << box.fill_level(measured_mass) << " ("
            << (box.fill_level(measured_mass) / box.height) * 100 << "% full)\n";

  std::cout << "spare_capacity at " << fill_time << " = " << box.spare_capacity(measured_mass) << '\n';
  std::cout << "input flow rate after " << fill_time << " = " << measured_mass / fill_time << '\n';
  std::cout << "float rise rate = " << box.fill_level(measured_mass) / fill_time << '\n';
  const auto fill_time_left = (box.height / box.fill_level(measured_mass) - 1) * fill_time;
  std::cout << "box full E.T.A. at current flow rate = " << fill_time_left << '\n';

}
