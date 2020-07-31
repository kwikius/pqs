#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/concepts/associated/dimension_list.hpp>
#include <pqs/concepts/associated/dimensionally_equivalent.hpp>
#include <pqs/concepts/associated/dimension_definition.hpp>

namespace pqs{

   template < dimension Dx, dimension Dy>
   inline constexpr bool dimensionally_equivalent<Dx,Dy> =
      std::is_same_v<
         get_simple_dimension<Dx>,
         get_simple_dimension<Dy> 
      >;

   namespace impl{

      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            pqs::is_custom_dimension<Lhs> &&
            ! pqs::is_custom_dimension<Rhs> 
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
      > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::times,
         Rhs
      >{};

      // derived_dim * dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            ! is_custom_dimension<Lhs> &&
            is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
       > : pqs::binary_op<
         Lhs,
         pqs::times,
         get_simple_dimension<Rhs>
      >{};

      // derived_dim / derived_dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            pqs::is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
      > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::divides, 
         get_simple_dimension<Rhs>
      >{};

      // dim / derived_dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            ! pqs::is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
       > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::divides,
         Rhs
       >{};

      // derived_dim / dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            ! pqs::is_custom_dimension<Lhs> &&
              is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
       > : pqs::binary_op<
         Lhs,
         pqs::divides,
         get_simple_dimension<Rhs>
      >{};

      template <pqs::dimension Lhs, typename Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            pqs::is_ratio<Rhs>
      struct binary_op_impl <
         Lhs,
         struct pqs::to_power,
         Rhs
      > : pqs::binary_op<
            get_simple_dimension<Lhs>,
            struct pqs::to_power,
            Rhs
      >{};
      
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

   template <pqs::dimension Lhs, pqs::dimension Rhs>
   inline
   constexpr
   auto
   operator*( Lhs, Rhs ) 
   {
      return pqs::binary_op_t<Lhs,pqs::times,Rhs>{};
   }

   template <pqs::dimension Lhs, pqs::dimension Rhs>
   inline constexpr
   auto operator/( Lhs, Rhs ) 
   {
      return typename pqs::binary_op_t<Lhs,pqs::divides,Rhs>{};
   }

   template <int N, int D, pqs::dimension Dim>
      requires ( D != 0)
   inline constexpr
   auto pow( Dim )
   {
      return pqs::binary_op_t<Dim,struct pqs::to_power,std::ratio<N,D> >{};
   }

   template <int N, pqs::dimension Dim>
   inline constexpr
   auto  pow( Dim )
   {
      return pqs::binary_op_t<Dim,struct pqs::to_power,std::ratio<N,1> >{};
   }

   template < dimension DL, dimension DR>
   inline constexpr 
   auto operator==( DL, DR)
   {
      return dimensionally_equivalent<DL,DR>;
   }

   template < dimension DL, dimension DR>
   inline constexpr 
   auto operator!=( DL, DR)
   {
      return !dimensionally_equivalent<DL,DR>;
   }
} // pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
