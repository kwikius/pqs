#ifndef PQS_CONCEPTS_ASSOCIATED_DIMENSION_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_DIMENSION_DEFINITION_HPP_INCLUDED

#include <pqs/concepts/associated/dimension_list.hpp>
#include <pqs/concepts/associated/is_custom_dimension.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_dimension_impl =
        is_base_quantity_exponent<T> || 
        is_simple_dimension_list<T> ||
        is_custom_dimension<T>;
 
   } // impl

   template <typename T>
   inline constexpr bool is_dimension = 
      impl::is_dimension_impl< std::remove_cvref_t<T> >;

   template <typename T>
   concept dimension = is_dimension<T>;

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_DIMENSION_DEFINITION_HPP_INCLUDED
