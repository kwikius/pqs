#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/ratio.hpp>
#include <pqs/concepts/base_quantity.hpp>

namespace pqs{

   template <typename T>
   struct is_base_quantity_exp;

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
      struct base_quantity_exp_is_zero_impl : pqs::undefined {};

      template <typename UUID,typename Ratio,typename Where = void>
      struct make_base_quantity_exp_impl : pqs::undefined{};
   }

   template <typename T>
   struct is_base_quantity_exp : pqs::impl::is_base_quantity_exp_impl<T>{};

   template <typename T>
   struct get_base_quantity : pqs::impl::get_base_quantity_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct of_same_base_quantity : pqs::impl::of_same_base_quantity_impl<Lhs,Rhs>{};

   template <typename T>
   struct base_quantity_exp_is_zero : pqs::impl::base_quantity_exp_is_zero_impl<T>{};

   template <typename UUID, typename Ratio>
   struct make_base_quantity_exp : pqs::impl::make_base_quantity_exp_impl<N,D,UUID>{};

}


#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
