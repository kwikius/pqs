#ifndef PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <pqs/type_templates/base_unit.hpp>
#include <pqs/bits/base_quantities.hpp>

namespace pqs { 

   struct imperial_measurement_system { 
      using type = imperial_measurement_system; 
   };

}

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<
         pqs::imperial_measurement_system
      > : std::true_type{};
   }
}

namespace pqs{

   template <>
   struct base_unit<base_length,imperial_measurement_system>{
      static constexpr const char * symbol()
      {
         return "ft";
      }
   };

   template <>
   struct base_unit<base_mass,imperial_measurement_system>{
      static constexpr const char * symbol()
      {
         return "lb";
      }
   };

   template <>
   struct base_unit<base_time,imperial_measurement_system>{
      static constexpr const char * symbol()
      {
         return "s";
      }
   };
}

#endif // PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED