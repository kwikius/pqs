#ifndef PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED
#define PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>

namespace pqs{

   namespace detail{
      struct base_quantity_base_class{};
   }
   // Id must be meta::totally_ordered
   // base_quantity_of model of meta identity function
   template <typename Id>
   struct base_quantity_of : pqs::detail::base_quantity_base_class{
      static_assert(pqs::meta::are_totally_ordered<Id,Id>::value, 
      "base_quantity_of requires Id to be totally ordered at compile time");
      typedef Id identifier;
      typedef base_quantity_of type;
   };

   namespace impl{

      template <typename T>
         requires std::is_base_of_v<pqs::detail::base_quantity_base_class,T>
      inline constexpr bool is_base_quantity_impl<T> = true;

      template <typename T>
         requires std::is_base_of_v<pqs::detail::base_quantity_base_class,T>
      struct get_base_quantity_id_impl<T>{
          using type = typename T::identifier;
      };
   }
}//pqs

#endif // PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED
