#ifndef PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED

#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/bits/binary_op.hpp>

namespace pqs{

   namespace impl{

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<Lhs, pqs::divides,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
      >{
         // prob normalise this?
         typedef typename conversion_factor_normalise<
            pqs::conversion_factor<
               typename std::ratio_divide<
                  typename Lhs::multiplier,
                  typename Rhs::multiplier
               >::type,
               typename std::ratio_subtract<
                  typename Lhs::exponent,
                  typename Rhs::exponent
               >::type
            >
         >::type type;
      };

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<Lhs, pqs::times,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
      >{
         // prob normalise this?
         typedef typename conversion_factor_normalise<
            pqs::conversion_factor<
               typename std::ratio_multiply<
                  typename Lhs::multiplier,
                  typename Rhs::multiplier
               >::type,
               typename std::ratio_add<
                  typename Lhs::exponent,
                  typename Rhs::exponent
               >::type
            >
         >::type type;
      };

      

   } // impl

}//pqs

#endif // PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED
