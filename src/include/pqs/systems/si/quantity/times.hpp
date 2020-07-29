#ifndef PQS_SI_QUANTITY_TIMES_HPP_INCLUDED
#define PQS_SI_QUANTITY_TIMES_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/times.hpp>
#include <pqs/systems/si/unit.hpp>


namespace pqs{ namespace impl {


   /**
   * @brief si quantity multiplication semantic. 
   * If one or other of inputs is a proper_quantity
   * quantities are converted to proper_quantites quantities  before
   * multiply and reult is a proper quantity
   */
   template <quantity Lhs, quantity Rhs> 
      requires si::are_in_si_measurement_system<Lhs,Rhs>
        && ( si::is_normative_unit<get_unit<Lhs>  > ||
           si::is_normative_unit<get_unit<Rhs> > )
   struct dimensioned_out_semantic< Lhs, times, Rhs>{

      // type to convert Lhs to before calc
      using lhs_type = make_quantity<
         si::make_normative_unit<get_unit<Lhs> >,
         get_numeric_type<Lhs>
      >;

      // type to convert Rhs to before calc
      using rhs_type = make_quantity<
         si::make_normative_unit<get_unit<Rhs> >,
         get_numeric_type<Rhs>
      >;

      using result_dimension = 
         binary_op_t<
            get_simple_dimension<lhs_type>,
            times,
            get_simple_dimension<rhs_type>
         >;

      using result_conversion_factor = 
         binary_op_t<
            get_conversion_factor<lhs_type>,
            times,
            get_conversion_factor<rhs_type>
         >;

      using result_unit = si::normative_unit<
            result_dimension,
            typename result_conversion_factor::exponent
         >;
         
      using result_numeric_type =
         binary_op_t<
            get_numeric_type<Lhs>,
            times,
            get_numeric_type<Rhs>
         >;

      using result = make_quantity <
         result_unit,
         result_numeric_type
      >;

      static constexpr auto apply(Lhs const & lhs, Rhs const & rhs)
      {
         return result{
            get_numeric_value(implicit_cast<lhs_type>(lhs)) *
            get_numeric_value(implicit_cast<rhs_type>(rhs))
         };
      }
   };
}} // pqs::impl

#endif // PQS_CONCEPTS_QUANTITY_TIMES_QUANTITY_HPP_INCLUDED
