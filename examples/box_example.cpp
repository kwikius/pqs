


#include <pqs/systems/si/acceleration.hpp>
#include <pqs/systems/si/density.hpp>
#include <pqs/systems/si/force.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/volume.hpp>
#include <cassert>

using namespace pqs;

struct Box {
  static constexpr auto air_density = si::density::kg_per_m3<>{1.225};
  static constexpr auto g = si::acceleration::m_per_s2<>{9.98};

  si::length::m<> length;
  si::length::m<> width;
  si::length::m<> height;

  struct {
    si::density::kg_per_m3<> density = air_density;
  } contents;

  constexpr Box(const si::length::m<>& l, const si::length::m<>& w, const si::length::m<>& h) : length{l}, width{w}, height{h} {}

  constexpr si::force::N<> filled_weight() const
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
    //assert(density_in > air_density);
    contents.density = density_in;
  }
};

#include <iostream>

int main()
{
  auto box = Box(si::length::mm<>{1000.0}, si::length::mm<>{500.0},si::length::mm<>{200.0});
  box.set_contents_density(si::density::kg_per_m3<>{1000.0});

  const auto fill_time = si::time::s<>{200.0};      // time since starting fill
  const auto measured_mass = si::mass::kg<>{20.0};  // measured mass at fill_time

  std::cout << "pqs box example...\n";
  std::cout << "fill height at " << fill_time << " = " << box.fill_level(measured_mass) << " ("
            << (box.fill_level(measured_mass) / box.height) * 100 << "% full)\n";

  std::cout << "spare_capacity at " << fill_time << " = " << box.spare_capacity(measured_mass) << '\n';
  std::cout << "input flow rate after " << fill_time << " = " << measured_mass / fill_time << '\n';
  std::cout << "float rise rate = " << box.fill_level(measured_mass) / fill_time << '\n';
  const auto fill_time_left = (box.height / box.fill_level(measured_mass) - 1) * fill_time;
  std::cout << "box full E.T.A. at current flow rate = " << fill_time_left << '\n';

}
