#ifndef PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/instance/basic_quantity_fwd.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/meta/min.hpp>

   /**
   * @brief default multiplication op
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
         requires pqs::dimension<result_dimension<Lhs,Rhs> >
      struct result{
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
         requires std::is_same_v<result_dimension<Lhs,Rhs>,pqs::dimensionless>
      struct result{
         using type = std::remove_cvref_t<decltype(
            std::declval<get_numeric_type<Lhs> >() * 
            std::declval<get_numeric_type<Rhs> >()
         )>;
      };

      template <quantity Lhs, quantity Rhs>
         requires pqs::dimension<result_dimension<Lhs,Rhs> >
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(result_type{lhs}) * 
            get_numeric_value(result_type{rhs})
         };
      }

     template <quantity Lhs, quantity Rhs>
         requires std::is_same_v<result_dimension<Lhs,Rhs>,pqs::dimensionless>
      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {

         using result_type = typename result<Lhs,Rhs>::type;
         return result_type{
            get_numeric_value(result_type{lhs}) * 
#error TODO
            get_numeric_value(result_type{rhs})
         };
      }
   };
   
   template <quantity Lhs, quantity Rhs>
      provide_operator_times<Lhs,Rhs>
   inline constexpr auto operator * ( Lhs const & lhs, Rhs const & rhs)
   {
      return quantity_times_semantic<
         get_measurement_system<Lhs>,
         get_measurement_system<Rhs>
      >::apply(lhs, rhs);
   }

}

#endif // PQS_CONCEPTS_QUANTITY_TIMES_QUANTITY_HPP_INCLUDED
