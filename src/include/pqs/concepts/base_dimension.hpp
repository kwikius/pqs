#ifndef PQS_CONCEPTS_BASE_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_DIMENSION_HPP_INCLUDED

#include <type_traits>

#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace pqs{

   template <typename T>
   struct is_base_dimension;

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_dimension_impl : std::false_type{};

      template <typename BaseDimLhs,typename BaseDimRhs, typename Where = void>
      base_dimension_less_impl : pqs::undefined{};

      template <typename BaseDimLhs,typename BaseDimRhs, 
        typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_dimension<BaseDimLhs>,
               pqs::is_base_dimension<BaseDimRhs>,
               pqs::meta::totally_ordered<BaseDimLhs,BaseDimRhs>
        >
        base_dimension_less_impl : pqs::undefined{};
      
      
   }

   template <typename T>
   struct is_base_dimension : impl::is_base_dimension_impl<T>{};

   // check that  less op is available
   // generic implementation of less and equal_to
   template <typename BaseDimLhs,typename BaseDimRhs>
   base_dimension_less : base_dimension_less_impl<BaseDimLhs,BaseDimRhs>{};


}

#endif // PQS_CONCEPTS_BASE_DIMENSION_HPP_INCLUDED
