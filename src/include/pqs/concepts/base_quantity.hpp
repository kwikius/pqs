#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/binary_op.hpp>

/**
*   base _quantity concept
*/

namespace pqs{

   namespace impl{

      /**
      * @brief default impl of opt in to being a base_quantity implementaion
      * @param Any type
      * @return default :false ( requires customisation)
      */
      template <typename T>
      inline constexpr 
      bool is_base_quantity_impl = false;
      
   } //impl

  /**
   * @brief interface opt in for base quantity
   */
   template <typename T>
   inline constexpr bool is_base_quantity = 
      impl::is_base_quantity_impl< 
         std::remove_cvref_t<T> 
      >;

   /**
   *  @brief implement base_quantity concept
   */
   template <typename T>
   concept base_quantity = is_base_quantity<T>;

   namespace impl{
     /**
      *  @brief default impl of default get_base_quantity_id 
      *  @param Qb model of base_quantity
      *  @return default : undefined ( requires customisation)
      */
      template <typename Qb>
      struct get_base_quantity_id_impl 
      : undefined_arg<Qb>{};
   }

   /**
   *  @brief Interface for get_base_quantity_id
   */
   template <base_quantity Qb>
   using get_base_quantity_id = 
      typename impl::get_base_quantity_id_impl<
         std::remove_cvref_t<Qb> 
      >::type;
   
   namespace impl{

      /**
      *  @brief provide base_quantity totally ordered ,less
      */
      template <base_quantity Lhs,base_quantity Rhs>
      struct binary_op_impl<
         Lhs,less, Rhs
      > : binary_op<
           get_base_quantity_id<Lhs>,
           less, 
           get_base_quantity_id<Rhs>
      >{};

      /**
      *  @brief provide base_quantity totally ordered , equal_to
      */
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
