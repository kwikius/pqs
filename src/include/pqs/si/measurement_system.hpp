#ifndef PQS_BITS_SI_QUANTITY_SYSTEM_HPP_INCLUDED
#define PQS_BITS_SI_QUANTITY_SYSTEM_HPP_INCLUDED

#include <pqs/type_templates/base_unit.hpp>
#include <pqs/bits/base_quantities.hpp>

namespace pqs{ 

   struct  si_measurement_system {
      using type = si_measurement_system;
   };

 } //pqs::si

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<
         pqs::si_measurement_system
       > : std::true_type{};
   }
}

namespace pqs{

   template <>
   struct  base_unit<base_length,si_measurement_system>{
      static constexpr const char * symbol()
      {
         return "m";
      }
      static constexpr int prefix_offset = 0;
   };

   template <>
   struct  base_unit<base_mass,si_measurement_system>{
      static constexpr const char * symbol()
      {
         return "g";
      }
      static constexpr int prefix_offset = 3;
   };

   // etc

}

#endif // PQS_BITS_SI_QUANTITY_SYSTEM_HPP_INCLUDED
