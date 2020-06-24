#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/concepts/dlist.hpp>

namespace pqs{ 

   namespace impl{

      template <typename D>
      struct binary_op_impl<
         D, pqs::times, pqs::dimensionless,
         typename pqs::where_<
            pqs::is_dimension<D>
         >::type
      > : D{};

      template <typename D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::times,D,
         typename pqs::where_<
            pqs::is_dimension<D>
         >::type
      > : D{};


      template <typename D>
      struct binary_op_impl<
         D, pqs::divides, pqs::dimensionless,
         typename pqs::where_<
            pqs::is_dimension<D>
         >::type
      > : D{};

      template <typename D>
      struct binary_op_impl<
         pqs::dimensionless, pqs::divides,D,
         typename pqs::where_<
            pqs::is_dimension<D>
         >::type
      > : D{};
   
   }



}

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
