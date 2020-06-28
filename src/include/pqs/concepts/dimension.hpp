#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/type_templates/dimension_list.hpp>

namespace pqs{ 

   namespace impl{

      template <typename D>
      struct binary_op_impl<
         D, pqs::times, pqs::dimensionless,
         typename pqs::where_<
            pqs::is_dimension_legacy<D>
         >::type
      > : D{};

      template <typename D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::times,D,
         typename pqs::where_<
            pqs::is_dimension_legacy<D>
         >::type
      > : D{};

      template <typename D>
      struct binary_op_impl<
         D, pqs::divides, pqs::dimensionless,
         typename pqs::where_<
            pqs::is_dimension_legacy<D>
         >::type
      > : D{};

      template <typename D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::divides,D,
         typename pqs::where_<
            pqs::is_dimension_legacy<D>
         >::type
      > : D{};
   
   } // impl

#if defined  __cpp_inline_variables

   template <typename T>
   constexpr bool is_dimension = is_dimension_legacy<T>::value;

   #if defined __cpp_concepts

   template <typename T>
   concept dimension = is_dimension<T>;

   #endif

#endif

} // pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
