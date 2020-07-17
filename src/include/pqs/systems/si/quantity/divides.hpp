#ifndef PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED
#define PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/divides.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace impl {

   /**
   * @brief custom si quantity dimensioned divide semantic
   * in si, if one or both is a proper si quantity
   * then convert both to proper si before calc
   *  result is also a proper si quantity
   */
   template <quantity Lhs, quantity Rhs> 
      requires si::are_in_si_measurement_system<Lhs,Rhs>
        && ( si::is_normative_unit<get_unit<Lhs>  > ||
           si::is_normative_unit<get_unit<Rhs> > )
   struct dimensioned_out_semantic< Lhs, divides, Rhs>{

      // type to convert Lhs to before calc
      using lhs_type = pqs::basic_quantity<
         si::make_normative_unit<get_unit<Lhs> >,
         get_numeric_type<Lhs>
      >;

      // type to convert Rhs to before calc
      using rhs_type = pqs::basic_quantity<
         si::make_normative_unit<get_unit<Rhs> >,
         get_numeric_type<Rhs>
      >;

      using result_dimension = 
         binary_op_t<
            get_simple_dimension<lhs_type>,
            divides,
            get_simple_dimension<rhs_type>
         >;

      using result_conversion_factor = 
         binary_op_t<
            get_conversion_factor<lhs_type>,
            pqs::divides,
            get_conversion_factor<rhs_type>
         >;

      using result_unit = si::normative_unit<
            result_dimension,
            typename result_conversion_factor::exponent
         >;
         
      using result_numeric_type =
         binary_op_t<
            get_numeric_type<Lhs>,
            divides,
            get_numeric_type<Rhs>
         >;

      using result = pqs::basic_quantity <
         result_unit,
         result_numeric_type
      >;

      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         return result{
            get_numeric_value(implicit_cast<lhs_type>(lhs)) / 
            get_numeric_value(implicit_cast<rhs_type>(rhs))
         };
      }
   };

   /**
   *  @brief customise si to return si normative_quantity
   */

   template <dimensionless_quantity V, quantity Q>
   requires si::is_normative_unit<get_unit<Q> >
   struct dimensionless_in_semantic<V, divides,Q>{

      using result_dimension = 
         unary_op_t<
            pqs::meta::reciprocal,
            get_simple_dimension<Q>
         >;
      
      using result_conversion_factor =
         unary_op_t<
            pqs::meta::reciprocal,
            get_conversion_factor<Q>
         >;

      using result_numeric_type =
         binary_op_t<V, divides, get_numeric_type<Q> >;

      using result = 
         basic_quantity<
            si::normative_unit<
               result_dimension,
               typename result_conversion_factor::exponent
            >,
            result_numeric_type
         >;

      static 
      constexpr auto apply(V const & v, Q const & q)
      {
         return result{v / get_numeric_value(q)};
      }
   };

}} // pqs::impl

#endif // PQS_CONCEPTS_QUANTITY_DIVIDES_QUANTITY_HPP_INCLUDED
