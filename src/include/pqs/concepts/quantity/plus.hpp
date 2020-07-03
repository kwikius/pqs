#ifndef PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_PLUS_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>

namespace pqs{

   template <
         typename MeasurementSystemLhs
         typename MeasurementSystemRhs
   >
   struct operator_plus;

   template <typename MeasurementSystem>
   struct operator_plus<MeasurementSystem,MeasurementSystem>
   {
      template <quantity Lhs, quantity Rhs>
      static auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = pqs::common_type<Lhs, Rhs>;
         return result_type{
            get_numeric_value(result_type{lhs})
               + get_numeric_value(result_type{rhs})
         };
      }
   }

   template <quantity Lhs, quantity Rhs>
   requires  (typename get_dimension<Lhs>{} == typename get_dimension<Rhs>{})
   && provide_operator_plus<Lhs,Rhs>
   inline auto operator + ( Lhs const & lhs, rhs const & rhs)
   {
      return operator_plus<
         typename get_measurement_system<Lhs>,
         typename get_measurement_system<Rhs>
      >::template apply(lhs, rhs);
   }

}

#endif // PQS_CONCEPTS_QUANTITY_PLUS_QUANTITY_HPP_INCLUDED
