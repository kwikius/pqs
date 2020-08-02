#ifndef PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_unit_impl = false;
   }

   template <typename T>
   concept unit = impl::is_unit_impl< 
      std::remove_cvref_t<T> 
   >;

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_UNIT_DEFINITION_HPP_INCLUDED
