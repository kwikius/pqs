#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/binary_op.hpp>

namespace pqs{

/*
   model of base quantity requires
     meta::totally_ordered
     meta::identity_function
*/
   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_impl : std::false_type{};
      
      // get_uuid. 
      template <typename BaseQuantity, typename Where = void>
      struct get_base_quantity_id_impl : pqs::undefined_arg<BaseQuantity>{};

   } //impl

   template <typename T>
   struct is_base_quantity_legacy : impl::is_base_quantity_impl<T>{};

#if defined  __cpp_inline_variables

   template <typename T>
   inline constexpr bool is_base_quantity = is_base_quantity_legacy<T>::value;

   #if defined __cpp_concepts

   template <typename T>
   concept base_quantity = is_base_quantity<T>;

   #endif

#endif

   template <typename BaseQuantity>
   struct get_base_quantity_id : impl::get_base_quantity_id_impl<BaseQuantity>{};
   
   namespace impl{

      template <typename Lhs,typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::less, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
              pqs::is_base_quantity_legacy<Lhs>,
              pqs::is_base_quantity_legacy<Rhs>
            >
         >::type 
      > : pqs::binary_op<
           typename get_base_quantity_id<Lhs>::type,
           pqs::less, 
           typename get_base_quantity_id<Rhs>::type
      >{};

      template <typename Lhs,typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
              pqs::is_base_quantity_legacy<Lhs>,
              pqs::is_base_quantity_legacy<Rhs>
            >
         >::type 
      > : pqs::binary_op<
         typename get_base_quantity_id<Lhs>::type,
         pqs::equal_to, 
         typename get_base_quantity_id<Rhs>::type
      >{};
      
   } //impl
} //pqs

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
