#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/totally_ordered.hpp>

#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/binary_op.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr 
      bool is_base_quantity_impl = false;

      template <typename BaseQuantity>
      struct get_base_quantity_id_impl 
      : undefined_arg<BaseQuantity>{};
      
   } //impl

   template <typename T>
   inline constexpr bool is_base_quantity = 
      impl::is_base_quantity_impl< 
         std::remove_cvref_t<T> 
      >;

   template <typename T>
   concept base_quantity = is_base_quantity<T>;

   template <typename BaseQuantity>
   using get_base_quantity_id = 
      typename impl::get_base_quantity_id_impl<
         std::remove_cvref_t<BaseQuantity> 
      >::type;
   
   namespace impl{

      template <base_quantity Lhs,base_quantity Rhs>
      struct binary_op_impl<
         Lhs,less, Rhs
      > : binary_op<
           get_base_quantity_id<Lhs>,
           less, 
           get_base_quantity_id<Rhs>
      >{};

      template <base_quantity Lhs,base_quantity Rhs>
      struct binary_op_impl<
         Lhs,equal_to, Rhs
      > : binary_op<
         get_base_quantity_id<Lhs>,
         equal_to, 
         get_base_quantity_id<Rhs>
      >{};
      
   } //impl
} //pqs

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
