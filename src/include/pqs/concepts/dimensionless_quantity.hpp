#ifndef PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_dimensionless_quantity_impl = false;

      template <typename T>
         requires std::is_arithmetic_v<T>
      inline constexpr bool is_dimensionless_quantity_impl<T> = true;

   } // impl

   template <typename T>
   concept dimensionless_quantity = 
      impl::is_dimensionless_quantity_impl<
         std::remove_cvref_t<T>
      >;

} //pqs

#endif // PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
