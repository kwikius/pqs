#ifndef PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{

      template <typename T>
      struct is_dimensionless_quantity_impl : std::false_type{};

      template <typename T>
         requires std::is_arithmetic_v<T>
      struct is_dimensionless_quantity_impl<T> : std::true_type{};

   }

   template <typename T>
   constexpr inline bool is_dimensionless_quantity = 
   impl::is_dimensionless_quantity_impl<
      std::remove_cvref_t<T>
   >::value;

   template <typename T>
   concept dimensionless_quantity = is_dimensionless_quantity<T>;

} //pqs

#endif // PQS_CONCEPTS_DIMENSIONLESS_QUANTITY_HPP_INCLUDED
