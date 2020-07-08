#ifndef PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/concepts/quantity/times.hpp>
#include <pqs/si/measurement_system_def.hpp>
#include <pqs/si/unit.hpp>

   /**
   * @brief si quantity multiplication semantic. 
   * quantities are converted to quantities whose multiplier is one before
   * multiply
   */

namespace pqs{

   template <>
   struct quantity_times_semantic<pqs::si_measurement_system, pqs::si_measurement_system>
   {
      // dimension of Lhs* Rhs maybe a dimension or dimensionless
      template <quantity Lhs, quantity Rhs>
      using result_dimension = std::remove_cvref_t<
         decltype(
            std::declval<get_simple_dimension<Lhs> >() *
            std::declval<get_simple_dimension<Rhs> >()
         )
      >;

      template <quantity Lhs, quantity Rhs>
      struct dimensioned_result{
         using type = pqs::basic_quantity <
            pqs::basic_unit<
               S,
               result_dimension<Lhs,Rhs>,
               //TODO probably want only if one is si_unit and one is not
               // so if both si no need to convert
               // if both unit conversions then no need to convert
               pqs::binary_op_t<
                  pqs::si::make_coherent< get_conversion_factor<Lhs> >,
                  pqs::times,
                  pqs::si::make_coherent< get_conversion_factor<Rhs> >
               >
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
            pqs::times,
            pqs::get_conversion_factor<Rhs>
         >;
         using type = std::remove_cvref_t<decltype(
            std::declval<get_numeric_type<Lhs> >() * 
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
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(pqs::si::make_coherent<Lhs>{lhs}) * 
            get_numeric_value(pqs::si::make_coherent<Rhs>{rhs})
         };
      }

     template <quantity Lhs, quantity Rhs>
         requires std::is_same_v<result_dimension<Lhs,Rhs>,pqs::dimensionless>
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using cf = pqs::binary_op_t<
            pqs::get_conversion_factor<Lhs>,
            pqs::times,
            pqs::get_conversion_factor<Rhs>
         >;
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(lhs) * 
            get_numeric_value(rhs) * 
            pqs::evaluate<cf>()
         };
      }
   };
   
   template <quantity Lhs, quantity Rhs>
      requires provide_operator_times<Lhs,Rhs>
   inline constexpr auto operator * ( Lhs const & lhs, Rhs const & rhs)
   {
      return quantity_times_semantic<
         get_measurement_system<Lhs>,
         get_measurement_system<Rhs>
      >::apply(lhs, rhs);
   }
} // pqs

#endif // PQS_CONCEPTS_QUANTITY_TIMES_QUANTITY_HPP_INCLUDED
