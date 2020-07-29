#ifndef PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_unit_impl : std::false_type{};
   }

   template <typename T>
   inline constexpr bool is_unit = impl::is_unit_impl< 
      std::remove_cvref_t<T> 
   >::value;

   template <typename T>
   concept unit = is_unit<T>;

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED
