#ifndef PQS_CONCEPTS_QUANTITY_POW_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_POW_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/bits/basic_quantity_fwd.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/types/basic_unit.hpp>

namespace pqs{

   template <int N, int D, quantity Q>
      requires N != 0
   inline constexpr
   auto pow( Q const & q)
   {
      using exp10 = typename std::ratio<N,D>::type;
      // TODO 
      using result =
         pqs::basic_quantity<
            pqs::basic_unit<
               get_measurement_system<Q>,
               binary_op_t<
                  get_simple_dimension<Q>,
                  pqs::to_power,
                  exp10
               >,
               pqs::binary_op_t<
                  get_conversion_factor<Q>,
                  pqs::to_power,
                  exp10
               >
            >,
            double
         >;

      return result{
         std::pow(get_numeric_value(q),static_cast<double>(N)/D)
      };
   }

   template <int N, int D, quantity Q>
      requires N == 0
   inline constexpr
   auto pow( Q const & q)
   {
      return 1;
   }

}


#endif // PQS_CONCEPTS_QUANTITY_POW_HPP_INCLUDED
