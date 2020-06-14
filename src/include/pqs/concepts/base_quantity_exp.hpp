#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/ratio.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/concepts/base_quantity.hpp>

namespace pqs{

   /*
      Where T,Lhs,Rhs,are models of base_quantity_exp
        R is model of ratio
        B is a model of meta_bool_constant

      requires 
            binary_op<Lhs,times,Rhs> -> T
            binary_op<Lhs,divides,Rhs> -> T
            binary_op<Lhs,to_power,R> -> T;
            unary_op<reciprocal,Lhs> -> T
            binary_op<lhs,equal_to,Rhs> -> B
            binary_op<lhs,not_equal_to,Rhs> -> B
   */

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_exp_impl : std::false_type{};

      template <typename T, typename Where = void>
      struct get_base_quantity_impl : pqs::undefined{};
      
      template <typename Lhs, typename Rhs, typename Where = void>
      struct of_same_base_quantity_impl : std::false_type{};

      // derive default
      template <typename T, typename Where = void>
      struct base_quantity_exp_is_zero_impl : pqs::undefined_arg<T> {};

      // customise per UUID
      template <typename UUID,typename Ratio,typename Where = void>
      struct make_base_quantity_exp_impl : pqs::undefined_arg<UUID>{};

      template <typename T, typename Where = void >
      struct get_exponent_impl : pqs::undefined_arg<T>{};

   } //impl

   template <typename T>
   struct is_base_quantity_exp : pqs::impl::is_base_quantity_exp_impl<T>{};

   template <typename T>
   struct get_base_quantity : pqs::impl::get_base_quantity_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct of_same_base_quantity : pqs::impl::of_same_base_quantity_impl<Lhs,Rhs>{};

   template <typename T>
   struct base_quantity_exp_is_zero : pqs::impl::base_quantity_exp_is_zero_impl<T>{};

   template <typename UUID, typename Ratio>
   struct make_base_quantity_exp : pqs::impl::make_base_quantity_exp_impl<typename UUID::type, typename Ratio::type>{};

   template <typename T>
   struct get_exponent : impl::get_exponent_impl<T>{};

   template <typename T>
   struct is_derived_from_base_quantity_exp ;

   namespace impl{

      template <typename Lhs, typename Rhs>
      struct of_same_base_quantity_impl<
         Lhs,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            >
         >::type
       > : pqs::binary_op<
          typename pqs::get_base_quantity<Lhs>::type,
          pqs::equal_to,
          typename pqs::get_base_quantity<Rhs>::type
       >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::times, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::make_base_quantity_exp<
            typename get_base_quantity_id<
               typename pqs::get_base_quantity<Lhs>::type
            >::type,
            typename pqs::binary_op<
               typename get_exponent<Lhs>::type,
               pqs::plus,
               typename get_exponent<Rhs>::type
            >::type
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::divides, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::make_base_quantity_exp<
            typename get_base_quantity_id<
               typename pqs::get_base_quantity<Lhs>::type
            >::type,
            typename pqs::binary_op<
               typename get_exponent<Lhs>::type,
               pqs::minus,
               typename get_exponent<Rhs>::type
            >::type
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, struct pqs::to_power, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_ratio<Rhs>
            >
         >::type
      > : pqs::make_base_quantity_exp<
            typename get_base_quantity_id<
               typename pqs::get_base_quantity<Lhs>::type
            >::type,
            typename pqs::binary_op<
               typename get_exponent<Lhs>::type,
               pqs::times,
               typename Rhs::type
            >::type
      >{};

      template <typename T>
      struct unary_op_impl<
          pqs::meta::reciprocal,
          T,
          typename pqs::where_<
            pqs::is_base_quantity_exp<T> 
          >::type
      > : pqs::make_base_quantity_exp<
             typename get_base_quantity_id<
               typename pqs::get_base_quantity<T>::type
             >::type,
             typename pqs::unary_op<
               pqs::meta::negate,
               typename get_exponent<T>::type
             >::type
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::binary_op<
            typename get_exponent<Lhs>::type,
            pqs::equal_to,
            typename get_exponent<Rhs>::type
      >{};

     template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::not_equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::binary_op<
            typename get_exponent<Lhs>::type,
            pqs::not_equal_to,
            typename get_exponent<Rhs>::type
      >{};
 
      template <typename T>
      struct base_quantity_exp_is_zero_impl<
         T,
         typename pqs::where_<
             pqs::is_base_quantity_exp<T>
         >::type
      > : std::ratio_equal<
         typename get_exponent<T>::type,
         std::ratio<0> 
      >{};
   } //impl

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

      template <typename T>
      struct get_exponent_impl<
         T,
         typename pqs::where_<
            std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>
         >::type
      > {
         typedef typename T::exponent type;
      };

   }//impl

   template <typename T>
   struct is_derived_from_base_quantity_exp : pqs::meta::and_<
      std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>,
      pqs::meta::not_<pqs::is_base_quantity_exp<T> >
   >{};

}

#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
