#ifndef PQS_CONCEPTS_DIMENSIONLESS_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSIONLESS_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/binary_op.hpp>

/*

   A type representing dimensionlessness in dimensional analysis

   Where Lhs, Rhs, T is of type dimensionless
      binary_op<Lhs,*, Rhs> -> T
      binary_op<Lhs,/, Rhs> -> T
      binary_op<Lhs,==,Rhs> -> true_type
      binary_op<Lhs,!=,Rhs> -> false
*/

namespace pqs{

   struct dimensionless{
      using type = dimensionless;
      using exponent = std::ratio<0,1>;

      constexpr friend dimensionless operator * ( dimensionless,  dimensionless) {return {};}
      constexpr friend dimensionless operator / ( dimensionless,  dimensionless) {return {};}
      constexpr friend bool operator == ( dimensionless,  dimensionless) {return true;}
      constexpr friend bool operator != ( dimensionless,  dimensionless) {return false;}
   };

   namespace impl{

      template <typename T, typename Where >
      struct get_exponent_impl;

      template <>
      struct get_exponent_impl<dimensionless,void> {
         using type = std::ratio<0,1>;
      };

      template <>
      struct binary_op_impl<pqs::dimensionless, pqs::times,pqs::dimensionless> : pqs::dimensionless{};

      template <>
      struct binary_op_impl<pqs::dimensionless, pqs::divides,pqs::dimensionless> : pqs::dimensionless{};

      template <int N, int D>
      struct binary_op_impl<pqs::dimensionless, pqs::to_power,std::ratio<N,D> > : pqs::dimensionless{};

      template <>
      struct binary_op_impl<pqs::dimensionless, pqs::equal_to,pqs::dimensionless> : std::true_type{};

      template <>
      struct binary_op_impl<pqs::dimensionless, pqs::not_equal_to,pqs::dimensionless> : std::false_type{};

   } //impl

   

}


#endif // PQS_CONCEPTS_DIMENSIONLESS_HPP_INCLUDED
