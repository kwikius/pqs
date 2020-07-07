#ifndef PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/meta/min.hpp>

   /**
   * @brief default quantity multiplication semantic
   */

namespace pqs{

   template <typename LhsMS, typename RhsMS>
   struct quantity_times_semantic;

   template <measurement_system S>
   struct quantity_times_semantic<S,S>
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
               pqs::binary_op_t<
                  get_conversion_factor<Lhs>,
                  pqs::times,
                  get_conversion_factor<Rhs> 
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

#if 1
      template <quantity Lhs, quantity Rhs>
      struct result{
         using type = typename pqs::meta::eval_if_c<
            dimension<result_dimension<Lhs,Rhs> >,
               dimensioned_result<Lhs,Rhs>,
            dimensionless_result<Lhs,Rhs>
         >::type;
      };

#else
      template <quantity Lhs, quantity Rhs>
      struct result{
         using type = typename pqs::meta::eval_if<
            std::is_same<result_dimension<Lhs,Rhs>, pqs::dimensionless>,
               dimensionless_result<Lhs,Rhs>,
            dimensioned_result<Lhs,Rhs>
         >::type;
      };
#endif
      template <quantity Lhs, quantity Rhs>
         requires pqs::dimension<result_dimension<Lhs,Rhs> >
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(lhs) * 
            get_numeric_value(rhs)
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
            get_numeric_value(rhs) * pqs::evaluate<cf>()
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

}

#endif // PQS_CONCEPTS_QUANTITY_TIMES_QUANTITY_HPP_INCLUDED
