


#include <pqs/systems/si/length.hpp>

/*
  floor tiling. Work out how many tiles are needed as well as how much to cut off for half tiles
*/


using namespace pqs::si;
using namespace pqs::si::literals;


void tile_calc(length::mm<> const & floor_length, length::mm<> const &  tile_side, length::mm<> const &  tile_spacing)
{
  double const num_tiles = (floor_length - tile_spacing) / (tile_side + tile_spacing);
 
  int const num_full_tiles = static_cast<int>(num_tiles) - 1;

  length::m<> const extra = floor_length - ( (num_full_tiles + 1) * (tile_side + tile_spacing));

  length::m<> const half_tile = (extra + tile_side)/2;

  std::cout << "floor length (in) = " << floor_length <<'\n';

  std::cout << "num full = " << num_full_tiles <<'\n';
  std::cout << "half tile size = " << half_tile <<'\n';

  std::cout << "floor_length (out) = " << num_full_tiles * (tile_side + tile_spacing) + tile_spacing  + half_tile * 2 <<'\n'; 
}

 

int main()
{

  length::mm<> constexpr room_length = 2.0q_m;
  length::mm<> constexpr room_width = 1.45q_m;
  length::mm<> constexpr tile_side = 334.0q_mm;
  length::mm<> constexpr tile_spacing = 4.0q_mm;

  tile_calc(room_length,tile_side,tile_spacing);

  tile_calc(room_width,tile_side,tile_spacing);

}