#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/types/dimension_list.hpp>
#include <pqs/concepts/associated/dimensionally_equivalent.hpp>

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
      > : unary_op<pqs::meta::reciprocal,D>{};
   
   } // impl

   template < dimension Dx, dimension Dy>
   inline constexpr bool dimensionally_equivalent<Dx,Dy> =
      std::is_same_v<
         get_simple_dimension<Dx>,
         get_simple_dimension<Dy> 
      >;

   template < dimension DL, dimension DR>
   inline constexpr 
   auto operator ==( DL, DR)
   {
      return dimensionally_equivalent<DL,DR>;
   }

   template < dimension DL, dimension DR>
   inline constexpr 
   auto operator !=( DL, DR)
   {
      return !dimensionally_equivalent<DL,DR>;
   }
} // pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
