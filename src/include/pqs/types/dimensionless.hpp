#ifndef PQS_TYPES_DIMENSIONLESS_HPP_INCLUDED
#define PQS_TYPES_DIMENSIONLESS_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/binary_op.hpp>

/**
*   An instantiable type for representing dimensionlessness in dimensional analysis expressions
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

   template <int N, int D>
   constexpr inline dimensionless pow(dimensionless) { return {};}

   template <int N>
   constexpr inline dimensionless pow(dimensionless) { return {};}

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
