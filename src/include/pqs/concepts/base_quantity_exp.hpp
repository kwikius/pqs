#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/types/dimensionless.hpp>
#include <pqs/type_functions/get_base_quantity.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_base_quantity_exp_impl = false;

   } // impl

   template <typename T>
   inline constexpr bool is_base_quantity_exp = 
      impl::is_base_quantity_exp_impl< std::remove_cvref_t<T> >;

   template <typename T>
   concept base_quantity_exponent = is_base_quantity_exp<T>;

   namespace impl{

      template <typename Lhs, typename Rhs>
      inline constexpr auto of_same_base_quantity_impl = pqs::undefined_arg<Lhs,Rhs>{};

      template <base_quantity_exponent Lhs, base_quantity_exponent Rhs>
      inline constexpr bool of_same_base_quantity_impl<
         Lhs,Rhs
      > =  pqs::binary_op_v<
          get_base_quantity<Lhs>,
          pqs::equal_to,
          get_base_quantity<Rhs>
       >;

   } // impl

   template <typename Lhs, typename Rhs>
   inline constexpr bool of_same_base_quantity = pqs::impl::of_same_base_quantity_impl<
      std::remove_cvref_t<Lhs>,
      std::remove_cvref_t<Rhs>
   >;

// ########TODO remove legacy ##############
   template <typename Lhs, typename Rhs>
   struct of_same_base_quantity_legacy : std::bool_constant<
      pqs::of_same_base_quantity<Lhs,Rhs>
   >{};
//##########################################

   namespace impl{

      template <typename T>
      inline constexpr auto base_quantity_exp_is_zero_impl = pqs::undefined_arg<T>{};

      template <base_quantity_exponent T>
      inline constexpr bool base_quantity_exp_is_zero_impl<
         T 
       > = std::ratio_equal_v<get_exponent<T>, std::ratio<0> >;

      template <>
      inline constexpr bool base_quantity_exp_is_zero_impl<pqs::dimensionless> = true;

   } //impl

   template <typename T>
   inline constexpr bool base_quantity_exp_is_zero = impl::base_quantity_exp_is_zero_impl<
      std::remove_cvref_t<T>
   >;

   namespace impl{
      // customise per UUID
      template <typename UUID,typename Ratio,typename Where = void>
      struct make_base_quantity_exp_impl : pqs::undefined_arg<UUID>{};

   } //impl

   template <pqs::base_quantity Qb, typename Ratio>
   struct make_base_quantity_exp : pqs::meta::eval_if<
      std::bool_constant<(Ratio::num == 0)>,
         pqs::dimensionless,
      pqs::impl::make_base_quantity_exp_impl<
         get_base_quantity_id<Qb>, typename Ratio::type
      >
   >{};

   namespace detail{

      struct base_quantity_exp_base_class{}; 
   }

   namespace impl{

      template <typename T>
      struct get_base_quantity_impl<
         T,
         typename pqs::where_<
            std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>
         >::type
      > : T::base_type {};
   }

   namespace impl{

        template <typename T>
        inline constexpr bool is_custom_base_quantity_exp_impl 
            = std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T> &&
              ! pqs::is_base_quantity_exp<T>;
   }//impl

   template <typename T>
   inline constexpr bool is_custom_base_quantity_exp 
      = impl::is_custom_base_quantity_exp_impl<std::remove_cvref_t<T> >;

   namespace impl{

      template <typename T>
         requires std::is_base_of_v<
            pqs::detail::base_quantity_exp_base_class,T
         >
      struct get_exponent_impl<T> {
         using type = typename T::exponent;
      };

   }//impl

   namespace impl{

/*
    Lhs * Rhs  where Lhs,Rhs are of same base quantity
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

/*
   Lhs / Rhs  where Lhs,Rhs are of same base quantity
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

/*
      rational power
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

/*
      reciprocal
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

/* 
      equality
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

/*
   inequality
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
   } //impl
}

#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
