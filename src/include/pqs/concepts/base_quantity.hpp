#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>

#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace pqs{

/*
  Interesting on base_quantity v base_dimension
  http://www.science-campus.com/physics/measurement/meas_2_6.html
*/

/*
   concepts
    meta::totally_ordered
    meta::identity_function
*/

   template <typename T>
   struct is_base_quantity;

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_impl : std::false_type{};

//      template <typename BaseDimLhs,typename BaseDimRhs, typename Where = void>
//      struct base_quantity_less_impl : pqs::undefined{};
//      
//      template <typename BaseDimLhs,typename BaseDimRhs, typename Where = void>
//      struct base_quantity_equal_to_impl : pqs::undefined{};

   }

   template <typename T>
   struct is_base_quantity : impl::is_base_quantity_impl<T>{};
//
//   template <typename BaseDimLhs,typename BaseDimRhs>
//   struct base_quantity_less : impl::base_quantity_less_impl<BaseDimLhs,BaseDimRhs>{};
//
//   template <typename BaseDimLhs,typename BaseDimRhs>
//   struct base_quantity_equal_to : impl::base_quantity_equal_to_impl<BaseDimLhs,BaseDimRhs>{};
//
//   namespace impl {
//
//      // automatic once above metafunctions are defined
//      template <typename Lhs, typename Rhs>
//      struct binary_op_impl<
//         Lhs, pqs::meta::less, Rhs, 
//         typename pqs::where_<
//            pqs::meta::and_<
//               pqs::is_base_quantity<Lhs>,
//               pqs::is_base_quantity<Rhs>
//            >
//         >::type
//      > : base_quantity_less<Lhs,Rhs>{};
//
//      template <typename Lhs, typename Rhs>
//      struct binary_op_impl<
//         Lhs, pqs::meta::equal_to, Rhs, 
//         typename pqs::where_<
//            pqs::meta::and_<
//               pqs::is_base_quantity<Lhs>,
//               pqs::is_base_quantity<Rhs>
//            >
//         >::type
//      > : base_quantity_equal_to<Lhs,Rhs>{};
//
//   }

}

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
