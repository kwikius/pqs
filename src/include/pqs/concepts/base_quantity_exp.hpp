#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_exp_impl : std::false_type{};

      template <typename T, typename Where = void>
      struct get_base_quantity_impl : pqs::undefined{};
      
      template <typename Lhs, typename Rhs, typename Where = void>
      struct of_same_base_quantity_impl : std::false_type{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct add_base_quantity_exp_impl : pqs::undefined{};
   
      template <typename Lhs, typename Rhs, typename Where = void>
      struct subtract_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct multiply_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs, typename Where = void>
      struct divide_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Where = void>
      struct negate_base_quantity_exp_impl : pqs::undefined{};

      template <typename Lhs, typename Rhs>
      struct base_quantity_exp_equal_to_impl : pqs::undefined {};

      // derive default from equality ?
      template <typename Lhs, typename Rhs>
      struct base_quantity_exp_not_equal_impl : pqs::undefined {};

      // derive default
      template <typename T>
      struct base_quantity_exp_is_zero_impl : pqs::undefined {};
   }

   template <typename T>
   struct is_base_quantity_exp : pqs::impl::is_base_quantity_exp_impl<T>{};

   template <typename T, typename Where = void>
   struct get_base_quantity : pqs::impl::get_base_quantity_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct of_same_base_quantity : pqs::impl::of_same_base_quantity_impl< Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct add_base_quantity_exp : pqs::impl::add_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct subtract_base_quantity_exp : pqs::impl::subtract_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct multiply_base_quantity_exp : pqs::impl::multiply_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct divide_base_quantity_exp : pqs::impl::divide_base_quantity_exp_impl<Lhs,Rhs>{};

   template <typename T>
   struct negate_base_quantity_exp  : pqs::impl::negate_base_quantity_exp_impl<T>{};

   template <typename Lhs, typename Rhs>
   struct base_quantity_exp_equal_to : pqs::impl::base_quantity_exp_equal_to_impl<Lhs,Rhs>{};

   template <typename Lhs, typename Rhs>
   struct base_quantity_exp_not_equal : pqs::impl::base_quantity_exp_not_equal_impl<Lhs,Rhs>{};

   template <typename T>
   struct base_quantity_exp_is_zero : pqs::impl::base_quantity_exp_is_zero_impl<T>{};

}


#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_HPP_INCLUDED
