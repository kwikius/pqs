#ifndef PQS_CONCEPTS_ASSOCIATED_MEASUREMENT_SYSTEM_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_MEASUREMENT_SYSTEM_DEFINITION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T>
      struct is_measurement_system_impl : std::false_type{};
   }

   template <typename T>
   inline constexpr bool is_measurement_system = 
      impl::is_measurement_system_impl<
         std::remove_cvref_t<T> 
      >::value;

   template <typename T>
   concept measurement_system = is_measurement_system<T>;
}

#endif // PQS_CONCEPTS_ASSOCIATED_MEASUREMENT_SYSTEM_DEFINITION_HPP_INCLUDED
