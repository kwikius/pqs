#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>

#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace pqs{

   template <typename T>
   struct is_base_quantity;

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_impl : std::false_type{};

      template <typename BaseDimLhs,typename BaseDimRhs, typename Where = void>
      struct base_quantity_less_impl : pqs::undefined{};
      
      template <typename BaseDimLhs,typename BaseDimRhs, typename Where = void>
      struct base_quantity_equal_to_impl : pqs::undefined{};

   }

   template <typename T>
   struct is_base_quantity : impl::is_base_quantity_impl<T>{};

   template <typename BaseDimLhs,typename BaseDimRhs>
   struct base_quantity_less : impl::base_quantity_less_impl<BaseDimLhs,BaseDimRhs>{};

   template <typename BaseDimLhs,typename BaseDimRhs>
   struct base_quantity_equal_to : impl::base_quantity_equal_to_impl<BaseDimLhs,BaseDimRhs>{};

}

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
