#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/type_templates/dimension_list.hpp>

namespace pqs{ 

   namespace impl{

      template <pqs::dimension D>
      struct binary_op_impl<
         D, pqs::times, pqs::dimensionless
      > : D{};

      template <pqs::dimension D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::times, D
      > : D{};

      template <pqs::dimension D>
      struct binary_op_impl<
         D, pqs::divides, pqs::dimensionless
      > : D{};

      template <pqs::dimension D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::divides,D
      > : D{};
   
   } // impl

} // pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
