#ifndef PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <pqs/bits/undefined_arg.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_measurement_system_impl : std::false_type{};
   }

   template <typename T>
   inline constexpr bool is_measurement_system = 
      impl::is_measurement_system_impl<
         std::remove_cvref_t<T> 
      >::value;

   template <typename T>
   concept measurement_system = is_measurement_system<T>;

   template < typename TL, typename TR>
   inline constexpr auto same_measurement_system = undefined_arg<TR,TR>{};

   template <
      measurement_system SL,
      measurement_system SR
   > inline constexpr bool same_measurement_system<SL,SR> = 
      std::is_same_v<
         std::remove_cvref_t<SL>,std::remove_cvref_t<SR>
      >;

};

#endif // PQS_CONCEPTS_MEASUREMENT_SYSTEM_HPP_INCLUDED
