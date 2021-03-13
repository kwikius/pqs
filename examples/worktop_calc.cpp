
#include <pqs/systems/si/length.hpp>

using namespace pqs::si;
using namespace pqs::si::literals;

/*
 using pqs as a calculator. 
 The source makes a pleasing scripting language for simple calculations of this type
 with units expressed directly ( in my opinion!)
*/

int main()
{
   #define let auto constexpr

   let base_unit_floor_height = 870q_mm; // top of base unit above floor

   std::cout << "height floor to top of base unit = " << base_unit_floor_height << '\n';

   let worktop_thickness = 38q_mm; // thickness of laminated worktop

   let worktop_floor_height        // top of worktop fom floor
      = base_unit_floor_height 
      + worktop_thickness;

   std::cout << "height floor to top of worktop = " << worktop_floor_height << '\n';

   let hob_panbase_height = 35q_mm;  // height of hob pan base above worktop
   let hob_wallunit_clearance_height = 462q_mm; // from hob to lowest part of wall unit inc wallunit plinth
   let wallunit_plinth_height = 35q_mm; // plinth under wall unit

   let worktop_wallunit_bottom_clearance 
      = hob_panbase_height
      + hob_wallunit_clearance_height
      + wallunit_plinth_height
   ;
   std::cout << "clearance worktop to underside of wall_unit (not inc wall unit plinth ) = " 
      << worktop_wallunit_bottom_clearance
      << '\n';

   let wallunit_bottom_floor_height  // floor to underside of wall unit (not including plinth)
      = worktop_floor_height
      + worktop_wallunit_bottom_clearance
   ;
   std::cout << "height floor to underside of wall unit (not inc wall unit plinth) = "
      << wallunit_bottom_floor_height <<'\n';

   let wallunit_height = 720q_mm;  // top to bottom of wall unit without plinth or cornice

   let wallunit_top_floor_height  // floor to top of wall unit without wall unit cornice
      = wallunit_bottom_floor_height
      + wallunit_height
   ;

   std::cout << "height floor to top of wall unit (not inc wall unit cornice) = "
      << wallunit_top_floor_height <<'\n';

   let wallunit_fixing_height = 56q_mm; // height below top of wall unit for fixings

   let wallunit_floor_fixing_height = wallunit_top_floor_height - wallunit_fixing_height;

   std::cout << "height floor to wallunit fixing = " << wallunit_floor_fixing_height <<'\n';
   let cornice_height = 35q_mm; // cornice on top of wall unit
   let total_height_from_floor = wallunit_top_floor_height + cornice_height;

   std::cout << "height floor to top of wall unit inc cornice = " << total_height_from_floor << '\n';
}