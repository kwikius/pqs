#ifndef PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>

namespace pqs_exposition{

   namespace detail{
      struct base_quantity_exp_base{};

      template <typename T>
      struct is_base_quantity_exp : std::is_base_of<pqs_exposition::detail::base_quantity_exp_base,T>{};
   }

   template <typename BaseQuantity, int N, int D =1>
   struct exp : pqs_exposition::detail::base_quantity_exp_base{
      static_assert(pqs::is_base_quantity<BaseQuantity>::value,"Not a model of base_quantity");
      typedef BaseQuantity base_quantity;
      typedef typename std::ratio<N,D>::type ratio;
      typedef exp type;
   };

   template <typename BaseQuantity ,typename Ratio>
   struct make_base_quantity_exp : exp<typename BaseQuantity::type,Ratio::type::num, Ratio::type::den>{};

}

namespace pqs{

   // make pqs_exposition exp model of pqs::base_quantity_exp
   namespace impl{

      template <  typename T>
      struct is_base_quantity_exp_impl<
         T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > : std::true_type{};

      template <typename T>
      struct get_base_quantity_impl<
         T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > : T::base_quantity {};

      template <typename Lhs, typename Rhs>
      struct of_same_base_quantity_impl<
         Lhs,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>
            >
         >::type
       > : pqs::binary_op<
          typename pqs::get_base_quantity<Lhs>::type,
          pqs::meta::equal_to,
          typename pqs::get_base_quantity<Rhs>::type
       >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs,pqs::meta::plus, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            pqs::binary_op<typename Lhs::ratio,pqs::meta::plus,typename Rhs::ratio>
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::meta::minus, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            pqs::binary_op<typename Lhs::ratio,pqs::meta::minus,typename Rhs::ratio>
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::meta::times, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs::is_ratio<Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            pqs::binary_op<typename Lhs::ratio,pqs::meta::times,typename Rhs::type>
      >{};

      template <typename T>
      struct unary_op_impl<
          pqs::meta::negate,
          T,
          typename pqs::where_<
            pqs_exposition::detail::is_base_quantity_exp<T> 
          >::type
      > : pqs_exposition::make_base_quantity_exp<
             pqs::get_base_quantity<T>,
             pqs::unary_op<pqs::meta::negate,typename T::ratio>
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::meta::divides,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs::is_ratio<Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            pqs::binary_op<typename Lhs::ratio,pqs::meta::divides,typename Rhs::type>
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::meta::equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::binary_op<typename Lhs::ratio,pqs::meta::equal_to,typename Rhs::ratio>{};

     template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::meta::not_equal_to, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs::binary_op<typename Lhs::ratio,pqs::meta::not_equal_to,typename Rhs::ratio>{};

     
/*
      template <typename Lhs, typename Rhs>
      struct add_base_quantity_exp_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            std::ratio_add<typename Lhs::ratio,typename Rhs::ratio>
      >{};

      template <typename Lhs, typename Rhs>
      struct subtract_base_quantity_exp_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            std::ratio_subtract<typename Lhs::ratio,typename Rhs::ratio>
      >{};

      template <typename T>
      struct negate_base_quantity_exp_impl<
          T,
          typename pqs::where_<
            pqs_exposition::detail::is_base_quantity_exp<T> 
          >::type
      > : pqs_exposition::make_base_quantity_exp<
             pqs::get_base_quantity<T>,
             std::ratio_subtract<std::ratio<0,1>,typename T::ratio>
      >{};

      template <typename Lhs, typename Rhs>
      struct multiply_base_quantity_exp_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs::is_ratio<Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            std::ratio_multiply<typename Lhs::ratio,typename Rhs::type>
      >{};
 
      template <typename Lhs, typename Rhs>
      struct divide_base_quantity_exp_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs::is_ratio<Rhs>
            >
         >::type
      > : pqs_exposition::make_base_quantity_exp<
            pqs::get_base_quantity<Lhs>,
            std::ratio_divide<typename Lhs::ratio,typename Rhs::type>
      >{};
 
      template <typename Lhs, typename Rhs>
      struct base_quantity_exp_equal_to_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : std::ratio_equal<typename Lhs::ratio,typename Rhs::ratio>{};

      // derive default from equality ?
      template <typename Lhs, typename Rhs>
      struct base_quantity_exp_not_equal_impl<
         Lhs, Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs_exposition::detail::is_base_quantity_exp<Lhs>,
               pqs_exposition::detail::is_base_quantity_exp<Rhs>,
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : std::ratio_not_equal<typename Lhs::ratio,typename Rhs::ratio>{};
  */  
      template <typename T>
      struct base_quantity_exp_is_zero_impl<
         T,
         typename pqs::where_<
             pqs_exposition::detail::is_base_quantity_exp<T>
         >::type
      > : std::ratio_equal<typename T::ratio, std::ratio<0> >{};

   } // impl

} // pqs

#endif // PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
