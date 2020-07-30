#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_definition.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_is_zero.hpp>
#include <pqs/concepts/associated/make_base_quantity_exponent.hpp>
//#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>
#include <pqs/concepts/associated/is_custom_base_quantity_exponent.hpp>
#include <pqs/concepts/associated/of_same_base_quantity.hpp>
#include <pqs/concepts/associated/unary_op.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs{

#if 0
   namespace detail{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

      /**
      * @ brief convenience detect base class 
      */
      struct base_quantity_exp_base_class{}; 
     /** @} */
   }

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
         requires std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T>
      struct get_base_quantity_impl< T > : T::base_type {};
     /** @} */
   }

   namespace impl{

        template <typename T>
        inline constexpr bool is_custom_base_quantity_exp_impl = false;

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
        template <typename T>
          requires 
            std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T> &&
            ! pqs::is_base_quantity_exponent<T>
        inline constexpr bool is_custom_base_quantity_exp_impl<T> = true;
              
     /** @} */
   }//impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   inline constexpr bool is_custom_base_quantity_exp 
      = impl::is_custom_base_quantity_exp_impl<std::remove_cvref_t<T> >;
  /** @} */

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
         requires std::is_base_of_v<
            pqs::detail::base_quantity_exp_base_class,T
         >
      struct get_exponent_impl<T> {
         using type = typename T::exponent;
      };
     /** @} */

   }//impl

#endif

   namespace impl{
     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/

/**
 *  @brief Lhs * Rhs  where Lhs,Rhs are of same base quantity
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
      * @brief   Lhs / Rhs  where Lhs,Rhs are of same base quantity
      */
      template <
         pqs::base_quantity_exponent Lhs,
         pqs::base_quantity_exponent Rhs
      >  requires pqs::of_same_base_quantity<Lhs,Rhs>
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
       * @brief    reciprocal
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
       * @brief     equality
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

#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
