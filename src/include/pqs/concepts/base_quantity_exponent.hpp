#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>

#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/associated/unary_op.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/associated/dimensionless.hpp>
#include <pqs/concepts/associated/get_base_quantity.hpp>

namespace pqs{

/**
 *  @defgroup base_quantity_exponent_concept    base_quantity_exponent concept
 */

/**
 *  @defgroup base_quantity_exponent_concept_impl    base_quantity_exponent concept_impl
 */

/**
 *  @defgroup base_quantity_exponent_model    base_quantity_exponent model_of
 */

/**
 *  @defgroup named_dimension  named dimension
 */

   namespace impl{
      
     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
      inline constexpr bool is_base_quantity_exp_impl = false;
     /** @} */

   } // impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   inline constexpr bool is_base_quantity_exponent = 
      impl::is_base_quantity_exp_impl< std::remove_cvref_t<T> >;
  /** @} */

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   concept base_quantity_exponent = is_base_quantity_exponent<T>;
  /** @} */

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename Lhs, typename Rhs>
      inline constexpr auto of_same_base_quantity_impl = pqs::undefined_arg<Lhs,Rhs>{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <base_quantity_exponent Lhs, base_quantity_exponent Rhs>
      inline constexpr bool of_same_base_quantity_impl<
         Lhs,Rhs
      > =  pqs::binary_op_v<
          get_base_quantity<Lhs>,
          pqs::equal_to,
          get_base_quantity<Rhs>
       >;
     /** @} */

   } // impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename Lhs, typename Rhs>
   inline constexpr bool of_same_base_quantity = pqs::impl::of_same_base_quantity_impl<
      std::remove_cvref_t<Lhs>,
      std::remove_cvref_t<Rhs>
   >;
  /** @} */

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
      inline constexpr auto base_quantity_exp_is_zero_impl = pqs::undefined_arg<T>{};
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <base_quantity_exponent T>
      inline constexpr bool base_quantity_exp_is_zero_impl<
         T 
       > = std::ratio_equal_v<get_exponent<T>, std::ratio<0> >;
     /** @} */

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <>
      inline constexpr bool base_quantity_exp_is_zero_impl<pqs::dimensionless> = true;
     /** @} */

   } //impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <typename T>
   inline constexpr bool base_quantity_exp_is_zero = impl::base_quantity_exp_is_zero_impl<
      std::remove_cvref_t<T>
   >;
   /** @} */

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
     /**
      * @brief  customise per UUID
      */
      template <typename UUID,typename Ratio,typename Where = void>
      struct make_base_quantity_exp_impl : pqs::undefined_arg<UUID>{};
     /** @} */
   } //impl

  /**
   * @addtogroup base_quantity_exponent_concept
   * @{ **/
   template <pqs::base_quantity Qb, typename Ratio>
   struct make_base_quantity_exp : pqs::meta::eval_if<
      std::bool_constant<(Ratio::num == 0)>,
         pqs::dimensionless,
      pqs::impl::make_base_quantity_exp_impl<
         get_base_quantity_id<Qb>, typename Ratio::type
      >
   >{};
     /** @} */

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

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
        template <typename T>
        inline constexpr bool is_custom_base_quantity_exp_impl 
            = std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T> &&
              ! pqs::is_base_quantity_exponent<T>;
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
