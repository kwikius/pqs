#ifndef PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED
#define PQS_SI_QUANTITY_DIVIDES_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/divides.hpp>
#include <pqs/si/unit.hpp>

   /**
   * @brief custom si quantity dimensioned divide semantic
   * in si, if one or both is a proper si quantity
   * then convert both to proper si before calc
   *  result is also a proper si quantity
   */

namespace pqs{

   namespace impl {

      template <quantity Lhs, quantity Rhs> 
         requires si::are_in_si_measurement_system<Lhs,Rhs>
           && ( pqs::si::is_proper_si_unit<get_unit<Lhs>  > ||
              pqs::si::is_proper_si_unit<get_unit<Rhs> > )
      struct dimensioned_op_semantic< Lhs, divides, Rhs>{

         // type to convert Lhs to before calc
         using lhs_type = pqs::basic_quantity<
            pqs::si::make_proper_si_unit<get_unit<Lhs> >,
            get_numeric_type<Lhs>
         >;

         // type to convert Rhs to before calc
         using rhs_type = pqs::basic_quantity<
            pqs::si::make_proper_si_unit<get_unit<Rhs> >,
            get_numeric_type<Rhs>
         >;

         using result_dimension = 
            binary_op_t<
               get_simple_dimension<lhs_type>,
               divides,
               get_simple_dimension<rhs_type>
            >;

         using result_conversion_factor = 
            pqs::binary_op_t<
               get_conversion_factor<lhs_type>,
               pqs::divides,
               get_conversion_factor<rhs_type>
            >;

         using result_unit = si::proper_unit<
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
   } // impl
} // pqs

#endif // PQS_CONCEPTS_QUANTITY_DIVIDES_QUANTITY_HPP_INCLUDED
