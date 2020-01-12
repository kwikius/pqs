#ifndef PQS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>

#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/undefined.hpp>

namespace pqs{

   namespace detail{
      struct base_quantity_base_class{};
   }

   // Id must be meta::totally_ordered
   template <typename Id>
   struct base_quantity_of : pqs::detail::base_quantity_base_class{
      static_assert(pqs::meta::are_totally_ordered<Id,Id>::value, "base_quantity_of requires Id to be totally ordered at compile time");
      typedef Id identifier;
      typedef base_quantity_of type;
   };

   namespace impl{

      template <typename T>
      struct is_base_quantity_impl< 
         T,typename pqs::where_<std::is_base_of<pqs::detail::base_quantity_base_class,T> >::type
      > : std::true_type{};

      template <typename ID>
      struct get_base_quantity_id_impl< pqs::base_quantity_of<ID> > {
          typedef ID type;
      };

      // TODO could be more generic and move to concept
      template <typename Lhs,typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::less, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               std::is_base_of<pqs::detail::base_quantity_base_class,Lhs>,
               std::is_base_of<pqs::detail::base_quantity_base_class,Rhs>
            >
         >::type 
      > : pqs::binary_op<typename Lhs::identifier, pqs::less, typename Rhs::identifier>{};

      // TODO could be more generic and move to concept
      template <typename Lhs,typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               std::is_base_of<pqs::detail::base_quantity_base_class,Lhs>,
               std::is_base_of<pqs::detail::base_quantity_base_class,Rhs>
            >
         >::type 
      > : pqs::binary_op<typename Lhs::identifier, pqs::equal_to, typename Rhs::identifier>{};

   }

}//pqs

#endif // PQS_BASE_QUANTITY_HPP_INCLUDED
