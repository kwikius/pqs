#ifndef PQS_BITS_IS_UNDEFINED_HPP_INCLUDED
#define PQS_BITS_IS_UNDEFINED_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/meta/not.hpp>

namespace pqs{

    namespace impl{
      
      template  <typename T>
      struct is_undefined_impl : std::false_type{};
      
    }

   template <typename T>
   inline constexpr bool is_undefined = 
      impl::is_undefined_impl< std::remove_cvref_t<T> >::value;

   template <typename T>
   inline constexpr bool is_defined = ! is_undefined<T>;
}

#endif // PQS_BITS_IS_UNDEFINED_HPP_INCLUDED
