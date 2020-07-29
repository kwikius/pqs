#ifndef PQS_SYSTEMS_SI_QUANTITY_POW_HPP_INCLUDED
#define PQS_SYSTEMS_SI_QUANTITY_POW_HPP_INCLUDED

#include <pqs/concepts/quantity/pow.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

   /**
    * @brief refinement of pow for normative quantity
    * @param  normative_quantity
    * @return normative_quantity
    */
   template <int N, int D, quantity Q>
      requires N != 0 && si::is_normative_unit<get_unit<Q> >
   inline constexpr
   auto pow( Q const & q)
   {
      using exp10 = typename std::ratio<N,D>::type;

      using exp_in = typename get_conversion_factor<Q>::exponent::ratio;
      using exp_out = std::ratio_multiply<exp_in,exp10>;

      /* using exp_out = pqs::binary_op_t<
         typename get_conversion_factor<Q>::exponent,
         pqs::times,
         typename std::ratio<N,D>::type
         >;
      */
         
      using result =
         pqs::make_quantity<
            si::normative_unit<
               binary_op_t<
                  get_simple_dimension<Q>,
                  pqs::to_power,
                  exp10
               >,
               exponent10<exp_out::num,exp_out::den>
            >,
            double
         >;

      return result{
         std::pow(get_numeric_value(q),static_cast<double>(N)/D)
      };
   }

} //pqs

#endif // PQS_SYSTEMS_SI_QUANTITY_POW_HPP_INCLUDED
