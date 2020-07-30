#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXPONENT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_definition.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_is_zero.hpp>
#include <pqs/concepts/associated/make_base_quantity_exponent.hpp>
#include <pqs/concepts/associated/is_custom_base_quantity_exponent.hpp>
#include <pqs/concepts/associated/of_same_base_quantity.hpp>
#include <pqs/concepts/associated/unary_op.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs{

   namespace impl{
     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

     /**
       *  @brief Lhs * Rhs where Lhs,Rhs are of same base quantity
      */
      template <
         pqs::base_quantity_exponent Lhs,
         pqs::base_quantity_exponent Rhs
      >  requires pqs::of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl<Lhs,pqs::times,Rhs> 
      : pqs::make_base_quantity_exp<
         get_base_quantity<Lhs>,
         pqs::binary_op_t<
            get_exponent<Lhs>,
               pqs::plus,
                  get_exponent<Rhs>
         >
      >{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

     /**
      * @brief Lhs / Rhs where Lhs,Rhs are of same base quantity
      */
      template <
         pqs::base_quantity_exponent Lhs,
         pqs::base_quantity_exponent Rhs
      > 
         requires pqs::of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl<Lhs,pqs::divides,Rhs> 
      : pqs::make_base_quantity_exp<
         get_base_quantity<Lhs>,
         pqs::binary_op_t<
            get_exponent<Lhs>,
               pqs::minus,
                  get_exponent<Rhs>
         >
      >{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
     /**
      * @brief rational power
      */
      template <
         pqs::base_quantity_exponent Qbe,
         typename R
      >
         requires pqs::is_ratio<R>
      struct binary_op_impl<
         Qbe,struct pqs::to_power,R
      > : pqs::make_base_quantity_exp<
         get_base_quantity<Qbe> ,
         pqs::binary_op_t<
            get_exponent<Qbe>,
            pqs::times,
            typename R::type
         >
      >{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

     /**
       * @brief reciprocal
      */
      template <pqs::base_quantity_exponent T>
      struct unary_op_impl<
         pqs::meta::reciprocal,
         T
      > : pqs::make_base_quantity_exp<
         get_base_quantity<T>,
         typename pqs::unary_op<
            pqs::meta::negate,
            get_exponent<T>
         >::type
      >{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

     /** 
       * @brief  equality
      */
      template <
         pqs::base_quantity_exponent Lhs, 
         pqs::base_quantity_exponent Rhs
      > requires pqs::of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl<
         Lhs, pqs::equal_to, Rhs
      > : pqs::binary_op<
            get_exponent<Lhs>,
            pqs::equal_to,
            get_exponent<Rhs>
      >{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

     /**
       * @brief  inequality
      */
      template <
         pqs::base_quantity_exponent Lhs, 
         pqs::base_quantity_exponent Rhs
      > requires pqs::of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl<
         Lhs, pqs::not_equal_to, Rhs
      > : pqs::binary_op<
            get_exponent<Lhs>,
            pqs::not_equal_to,
            get_exponent<Rhs>
      >{}; 
     /** @} */
   } //impl
}

#endif // PQS_CONCEPTS_BASE_QUANTITY_EXPONENT_HPP_INCLUDED
