
#include <pqs/concepts/associated/quantity_to_fixed_string.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/current.hpp>
#include <pqs/systems/si/temperature.hpp>
#include <pqs/systems/si/substance.hpp>
#include <pqs/systems/si/intensity.hpp>
#include <pqs/systems/si/speed.hpp>
#include <pqs/systems/si/area.hpp>
#include <pqs/systems/si/acceleration.hpp>
#include <pqs/systems/imperial/length.hpp>

#include "test.hpp"

namespace {

   using namespace pqs;
   using namespace pqs::si::literals;

   void length_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_m) == "m");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_mm) == "mm");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_cm) == "cm");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_km) == "km");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_ft) == "ft");
   }

   void time_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_s) == "s");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_ms) == "ms");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_min) == "min");
   }

   void mass_out()
   {
       static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_kg) == "kg");
       static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_g) == "g");
   }

   void current_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_A) == "A");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_mA) == "mA");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_uA) == "\u00B5A");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_nA) == "nA");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_pA) == "pA");
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_fA) == "fA");
   }

   void temperature_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_K) == "K");
   }

   void substance_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_mol) == "mol");
   }

   void intensity_out()
   {
     static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_cd) == "cd");
   }

   void area_out()
   {
       static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_m2) == "m²");
       static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_mm2) == "mm²");
       static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_cm2) == "cm²");
   }

   void acceleration_out()
   {
      static_assert(unit_to_fixed_string<charset_utf8>(0.0_q_m_per_s2) == "m⋅s⁻²");
   }

   void sig_test()
   {
      using Qbe = pqs::exp_mass<-1,2>;
      using ms = pqs::si_measurement_system;
    #if 1
      using charset = pqs::charset_utf8;
    #else
      using charset = pqs::charset_ascii;
    #endif

      // base_dimension_exponent
      auto constexpr x = pqs::dimension_to_fixed_string<Qbe,ms,charset>();
     // std::cout << x <<'\n';

      // dimension_list
      using D = decltype( pqs::pow<3>(pqs::abstract_time_v) * pow<-3>(pqs::abstract_length_v) * pqs::pow<-1>(pqs::abstract_current_v));
   //   std::cout << pqs::dimension_to_fixed_string<D,ms,pqs::charset_utf8>() << '\n';
   //   std::cout << pqs::dimension_to_fixed_string<D,ms,pqs::charset_ascii>() << '\n';
      // custom dimension
      struct cd : decltype(pqs::abstract_length_v / pqs::pow<2>(pqs::abstract_time_v) ){};
   //   std::cout << pqs::dimension_to_fixed_string<cd,ms,pqs::charset_utf8>() << '\n';
   //   std::cout << pqs::dimension_to_fixed_string<cd,ms,pqs::charset_ascii>() << '\n';

      using Q = pqs::si::speed::m_per_s<>;
   //   std::cout <<  pqs::dimension_to_fixed_string<Q, pqs::charset_utf8>()  << '\n';
   //   std::cout <<  pqs::dimension_to_fixed_string<Q, pqs::charset_ascii>()  << '\n';

      using L = pqs::si::length::ft<>;
   //   std::cout <<  pqs::dimension_to_fixed_string<L, pqs::charset_utf8>()  << '\n';
   //   std::cout <<  pqs::dimension_to_fixed_string<L, pqs::charset_ascii>()  << '\n';

      using L1 = pqs::imperial::length::ft<>;
   //   std::cout <<  pqs::dimension_to_fixed_string<L1, pqs::charset_utf8>()  << '\n';
   //   std::cout <<  pqs::dimension_to_fixed_string<L1, pqs::charset_ascii>()  << '\n';

   }

   void literal_test()
   {
      auto constexpr q1 = 1.0_q_m;
      auto constexpr q2 = -1_q_m;
      auto constexpr q3 = 1.0_q_cm;
      auto constexpr q4 = -1_q_cm;
      auto constexpr q5 = 1.0_q_mm;
      auto constexpr q6 = -1_q_mm;
      auto constexpr q7 = 1.0_q_km;
      auto constexpr q8 = -1_q_km;
      auto constexpr q10 = 1.0_q_mm2;

   }

}

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else
void output_test()
#endif
{
   sig_test();

   length_out();
   time_out();
   mass_out();
   current_out();
   temperature_out();
   substance_out();
   intensity_out();
   area_out();
   acceleration_out();
   literal_test();
}
