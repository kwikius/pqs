
#include "atmosphere.hpp"
#include <pqs/systems/si/force.hpp>
#include <pqs/systems/si/area.hpp>
#include <pqs/systems/si/speed.hpp>

/**
 see https://en.wikipedia.org/wiki/Barometric_formula
**/

using namespace pqs;
using namespace si::literals;

namespace {
   
   using K_per_m = 
   make_v_quantity< si::temperature_unit::K() / si::length_unit::m()>;

   constexpr K_per_m operator "" q_K_per_m ( long double v)
   {
      return K_per_m{static_cast<double>(v)};
   }

   struct baro_constants_t{
      si::length::m<>            const ref_height_asl;
      si::pressure::Pa<>         const ref_pressure;
      si::density::kg_per_m3<>   const ref_density;
      si::temperature::K<>       const ref_temperature;
      K_per_m                    const lapse_rate;
   };    

   baro_constants_t constexpr 
   baro_constants[] = {
     {      0.0q_m , 101'325.00q_Pa , 1.225000q_kg_per_m3 , 288.15q_K , -0.0065q_K_per_m },
     { 11'000.0q_m ,  22'632.10q_Pa , 0.363910q_kg_per_m3 , 216.65q_K ,  0.0000q_K_per_m },
     { 20'000.0q_m ,   5'474.89q_Pa , 0.088030q_kg_per_m3 , 216.65q_K ,  0.0010q_K_per_m },
     { 32'000.0q_m ,     868.02q_Pa , 0.013220q_kg_per_m3 , 228.65q_K ,  0.0028q_K_per_m },
     { 47'000.0q_m ,     110.91q_Pa , 0.001430q_kg_per_m3 , 270.65q_K ,  0.0000q_K_per_m },
     { 51'000.0q_m ,      66.94q_Pa , 0.000860q_kg_per_m3 , 270.65q_K , -0.0028q_K_per_m },
     { 71'000.0q_m ,       3.96q_Pa , 0.000064q_kg_per_m3 , 214.65q_K , -0.0020q_K_per_m }
   };

   int get_baro_constant_idx(si::length::m<> const & asl)
   {
      int constexpr n = sizeof(baro_constants)/sizeof(baro_constants[0]) - 1;
      for ( int i = 0; i < n ;++i){
         if ( asl < baro_constants[i + 1].ref_height_asl){
            return i;
         }
      }
      return n;
   };

}

si::density::kg_per_m3<> 
air::get_density(pqs::si::length::m<> const & asl)
{
   int const idx = get_baro_constant_idx(asl);
   auto const & bc = baro_constants[idx];
  
   auto const rhoB = bc.ref_density;
   auto const Tb = bc.ref_temperature;
   auto const Lb = bc.lapse_rate;
   auto const hb = bc.ref_height_asl;

   auto constexpr R = make_v_quantity<
      si::energy_unit::J() / ( si::substance_unit::mol() * si::temperature_unit::K())
   >{8.3144598};

   auto constexpr g0 = 9.80665q_m_per_s2;

   auto constexpr M = make_v_quantity<
      si::mass_unit::kg() / si::substance_unit::mol()
   >{0.0289644};

   if ( bc.lapse_rate == 0.0q_K_per_m){
      return rhoB * std::exp( 
            (-g0  * M * (asl - hb))/( R * Tb)
         );
   }else{
      auto const exponent = ( 1 + (g0 * M)/(R * Lb));
      return rhoB 
         * std::pow(
               Tb / ( Tb + Lb  * ( asl - hb) ), 
               exponent
          );
   }
}

si::pressure::Pa<>
air::get_static_pressure(si::length::m<> const & asl)
{
   int const idx = get_baro_constant_idx(asl);
   auto const & bc = baro_constants[idx];
  
   auto const Pb = bc.ref_pressure;
   auto const Tb = bc.ref_temperature;
   auto const Lb = bc.lapse_rate;
   auto const hb = bc.ref_height_asl;

   auto constexpr R = make_v_quantity<
      si::energy_unit::J() / ( si::substance_unit::mol() * si::temperature_unit::K())
   >{8.3144598};

   auto constexpr g0 = 9.80665q_m_per_s2;

   auto constexpr M = make_v_quantity<
      si::mass_unit::kg() / si::substance_unit::mol()
   >{0.0289644};

   if ( bc.lapse_rate == 0.0q_K_per_m){
      return Pb * 
         std::exp(
            (g0 * -1 * M * ( asl - hb))/( R * Tb)
         );
   }else{
      auto const exponent = (-g0  * M )/ ( R * Lb);
      return  Pb * 
         std::pow(
            ( (Tb + Lb * ( asl - hb) )/ Tb )
            ,exponent
         ); 
   }
}

using namespace pqs;
using namespace si::literals;

namespace {

   si::force::N<> 
   get_lift(
      double const & Cl, 
      si::area::m2<> const & s,
      si::speed::m_per_s<> const & v,
      si::length::m<> const & asl
   )
   {
      return 0.5 * Cl * air::get_density(asl) * pow<2,1>(v) * s;
   }

   double get_CL(
      si::force::N<> const & lift,
      si::area::m2<> const & s,
      si::speed::m_per_s<> const & v,
      si::length::m<> const & asl
   ){
      return (2.0 * lift ) / (air::get_density(asl) * pow<2,1>(v) * s);
   }
}

int main()
{
   std::cout << air::specific_gas_constant() << '\n';
   std::cout << air::get_sea_level_pressure() << '\n';

   std::cout << air::get_static_pressure(100.0q_m ) << '\n';
   std::cout << air::get_density(100.0q_m ) << '\n';

   std::cout << air::get_static_pressure(100.0q_m ) / air::get_sea_level_pressure() <<'\n';

   // sea level lift
   si::force::N<> weight = get_lift(
      0.5,
      2q_m * 0.15q_m,
      10q_m_per_s,
      0q_m
   );

   std::cout << get_lift(
      0.5,
      2q_m * 0.15q_m,
      10q_m_per_s,
      100q_m
   ) << '\n';

   std::cout << get_lift(
      0.5,
      2q_m * 0.15q_m,
      10q_m_per_s,
      10000q_m
   ) << '\n';

   // note how higher CL is required at altitude
   double CL = get_CL(
      weight,  
      2q_m * 0.15q_m, 
      10q_m_per_s,
      1.0q_km
   );

   std::cout << "CL =" << CL << '\n';
   
}
  
