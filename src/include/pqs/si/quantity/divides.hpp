#ifndef PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED
#define PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/divides.hpp>
#include <pqs/si/unit.hpp>

   /**
   * @brief si quantity division semantic
   */

namespace pqs{

   template <>
   struct quantity_divides_semantic<      
      pqs::si_measurement_system, 
      pqs::si_measurement_system
   >
   {
      // dimension of Lhs / Rhs maybe a dimension or dimensionless
      template <quantity Lhs, quantity Rhs>
      using result_dimension = std::remove_cvref_t<
         decltype(
            std::declval<get_simple_dimension<Lhs> >() /
            std::declval<get_simple_dimension<Rhs> >()
         )
      >;

      template <quantity Lhs, quantity Rhs>
      struct dimensioned_result{
         
         using lhs_type = pqs::basic_quantity<
            pqs::si::make_proper_si_unit<get_unit<Lhs> >,
            get_numeric_type<Lhs>
         >;
         using rhs_type = pqs::basic_quantity<
            pqs::si::make_proper_si_unit<get_unit<Rhs> >,
            get_numeric_type<Rhs>
         >;

         using type = pqs::basic_quantity <
            pqs::si::proper_unit<
               result_dimension<Lhs,Rhs>,
               typename pqs::binary_op_t<
                  get_conversion_factor<lhs_type>,
                  pqs::divides,
                  get_conversion_factor<rhs_type>
               >::exponent
            >,
            std::remove_cvref_t<decltype(
               std::declval<get_numeric_type<Lhs> >() * 
               std::declval<get_numeric_type<Rhs> >()
            )>
         >;
      };

      template <quantity Lhs, quantity Rhs>
      struct dimensionless_result{
         using cf = pqs::binary_op_t<
            pqs::get_conversion_factor<Lhs>,
            pqs::divides,
            pqs::get_conversion_factor<Rhs>
         >;
         using type = std::remove_cvref_t<decltype(
            std::declval<get_numeric_type<Lhs> >() / 
            std::declval<get_numeric_type<Rhs> >() * 
            pqs::evaluate<cf>()
         )>;
      };

      template <quantity Lhs, quantity Rhs>
      struct result{
         using type = typename pqs::meta::eval_if_c<
            dimension<result_dimension<Lhs,Rhs> >,
               dimensioned_result<Lhs,Rhs>,
            dimensionless_result<Lhs,Rhs>
         >::type;
      };

      template <quantity Lhs, quantity Rhs>
         requires pqs::dimension<result_dimension<Lhs,Rhs> >
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using lhs_type = typename dimensioned_result<Lhs,Rhs>::lhs_type;
         using rhs_type = typename dimensioned_result<Lhs,Rhs>::rhs_type;
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(implicit_cast<lhs_type>(lhs)) / 
            get_numeric_value(implicit_cast<rhs_type>(rhs))
         };
      }

     // n.b same as default
     template <quantity Lhs, quantity Rhs>
         requires std::is_same_v<result_dimension<Lhs,Rhs>,pqs::dimensionless>
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using cf = pqs::binary_op_t<
            pqs::get_conversion_factor<Lhs>,
            pqs::divides,
            pqs::get_conversion_factor<Rhs>
         >;
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            (get_numeric_value(lhs) / get_numeric_value(rhs)) * 
            pqs::evaluate<cf>()
         };
      }
   };
   
} // pqs

#endif // PQS_CONCEPTS_QUANTITY_DIVIDES_QUANTITY_HPP_INCLUDED
