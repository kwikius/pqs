#ifndef PQS_SI_QUANTITY_MINUS_HPP_INCLUDED
#define PQS_SI_QUANTITY_MINUS_HPP_INCLUDED

#include <pqs/bits/implicit_cast.hpp>
#include <pqs/concepts/quantity/minus.hpp>
#include <pqs/systems/si/unit.hpp>


namespace pqs { namespace impl{

      /**
    * @brief. Implement a custom - semantic for the 
    * si measurement system.
    *
    * if the quantities are the same then
    *    the result is the same as both
    * else if one or both quantities is a proper si_quantity then
    *    get finest grained and convert it to a proper si quantity
    * else
    *    get finest grained 
    *   
   */
      template < quantity Lhs, quantity Rhs> 
         requires ( pqs::si::is_normative_unit<get_unit<Lhs> > ||
              pqs::si::is_normative_unit<get_unit<Rhs> > )
         
      struct binary_op_semantic< Lhs, minus, Rhs>{
         //TODO here want to grab same dim if poss
         using result_unit = 
            pqs::si::make_normative_unit<
               std::conditional_t<
                  pqs::binary_op_v<
                     get_conversion_factor<Lhs>,
                     pqs::less_equal,
                     get_conversion_factor<Rhs> 
                  >,
                  get_unit<Lhs>,
                  get_unit<Rhs>
               >
            >;

         using lhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Lhs>,
               divides,
               get_conversion_factor<result_unit>
            >;

         using rhs_conversion_factor = 
            binary_op_t<
               get_conversion_factor<Rhs>,
               divides,
               get_conversion_factor<result_unit>
            >;

         using result_numeric_type =
            std::remove_cvref_t<
               decltype(
                  std::declval< get_numeric_type<Lhs> >()
                     * evaluate< lhs_conversion_factor >() -
                  std::declval< get_numeric_type<Rhs> >()
                     * evaluate< rhs_conversion_factor >()
               )
            >;
         using result = basic_quantity<
            result_unit,
            result_numeric_type
         >;

         static constexpr
         auto apply(Lhs const & lhs, Rhs const & rhs)
         {
            return result{
               get_numeric_value(implicit_cast<result>(lhs)) -
               get_numeric_value(implicit_cast<result>(rhs))
            };
         }
      };

}}// pqs::impl

#endif // PQS_SI_OPERATIONS_MINUS_HPP_INCLUDED
