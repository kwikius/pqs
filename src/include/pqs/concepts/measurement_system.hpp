#ifndef PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_measurement_system_impl : std::false_type{};

   }

   template < typename  T>
   struct is_measurement_system_legacy : impl::is_measurement_system_impl<T>{};

   template <typename T>
   inline constexpr bool is_measurement_system = is_measurement_system_legacy<T>::value;


   template <typename T>
   concept measurement_system = is_measurement_system<T>;

};

#endif // PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED
