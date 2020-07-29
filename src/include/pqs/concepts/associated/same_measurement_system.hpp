#ifndef PQS_CONCEPTS_ASSOCIATED_SAME_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_SAME_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <pqs/concepts/associated/measurement_system_definition.hpp>

namespace pqs{

   template < typename TL, typename TR>
   inline constexpr auto same_measurement_system = false;

   template <
      measurement_system SL,
      measurement_system SR
   > inline constexpr bool same_measurement_system<SL,SR> = 
      std::is_same_v<
         std::remove_cvref_t<SL>,std::remove_cvref_t<SR>
      >;

}


#endif // PQS_CONCEPTS_ASSOCIATED_SAME_MEASUREMENT_SYSTEM_HPP_INCLUDED
