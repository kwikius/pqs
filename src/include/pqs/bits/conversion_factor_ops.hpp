#ifndef PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED

#include <pqs/bits/conversion_factor_fwd.hpp>
#include <pqs/bits/detail/to_ll_conversion_factor.hpp>
#include <pqs/bits/detail/to_conversion_factor.hpp>
#include <pqs/bits/detail/conversion_factor_normalise.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs{

   namespace detail{

   // return 1 if  lhs > rhs
   // return 0 if Lhs == Rhs,
   // return -1 if lhs < rhs

      template <typename LLConvFactorLhs, typename LLConvFactorRhs>
      struct ll_conversion_factor_compare{
         typedef typename pqs::detail::ll_conversion_factor_normalise<LLConvFactorLhs>::type lhs_type;
         typedef typename pqs::detail::ll_conversion_factor_normalise<LLConvFactorRhs>::type rhs_type;
         typedef typename pqs::meta::eval_if<
            std::ratio_less<typename lhs_type::exponent,typename rhs_type::exponent>,
               std::integral_constant<int,-1>,
            std::ratio_greater<typename lhs_type::exponent,typename rhs_type::exponent>,
               std::integral_constant<int,1>,
            std::ratio_equal<typename lhs_type::multiplier,typename rhs_type::multiplier>,
               std::integral_constant<int,0>,
            std::ratio_greater<typename lhs_type::multiplier,typename rhs_type::multiplier>,
               std::integral_constant<int,1>,
            std::integral_constant<int,-1>
         >::type type;
         static constexpr int value = type::value;
      };

      // addition of two conv  
      // only possible for rational powers if both  have same denominator
      template <typename LLConvFactorLhs, typename LLConvFactorRhs>
      struct ll_conversion_factor_add{

         typedef typename pqs::detail::ll_conversion_factor_normalise<LLConvFactorLhs>::type lhs_type;
         typedef typename pqs::detail::ll_conversion_factor_normalise<LLConvFactorRhs>::type rhs_type;

         typedef typename detail::ll_conversion_factor_compare<lhs_type,rhs_type>::type comp_type;

         // align the conversion_factors so that the exponents are the same
         // N.B this can only work if the conversion_factor::exponent denominators are the same
         static_assert(lhs_type::exponent::den == rhs_type::exponent::den, "conversion_factor add: Exponent::denoms must be same");
         typedef typename pqs::meta::eval_if<
            std::integral_constant<bool,(comp_type::value == 0)>,
               lhs_type,
            std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller, so adjust rhs
               pqs::detail::ll_conversion_factor_add_exp_n<rhs_type, lhs_type::exponent::num - rhs_type::exponent::num>,
            pqs::detail::ll_conversion_factor_add_exp_n<lhs_type, rhs_type::exponent::num - lhs_type::exponent::num>
         >::type aligned_type;

         typedef typename pqs::meta::eval_if<
            std::integral_constant<bool,(comp_type::value == 0)>,
               pqs::detail::ll_conversion_factor<
                  typename std::ratio_add<
                     typename lhs_type::multiplier,
                     typename lhs_type::multiplier
                  >::type,
                  typename aligned_type::exponent
                >,
            std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller so use 
               pqs::detail::ll_conversion_factor<
                  typename std::ratio_add<
                     typename lhs_type::multiplier,
                     typename aligned_type::multiplier
                  >::type,
                  typename aligned_type::exponent
               >,
            pqs::detail::ll_conversion_factor<
               typename std::ratio_add<
                  typename aligned_type::multiplier,
                  typename rhs_type::multiplier
               >::type,
               typename aligned_type::exponent
            >
         >::type result_type;

        typedef typename pqs::detail::ll_conversion_factor_normalise<result_type>::type type;
         
      };

   } // detail

// ll 
   namespace impl{
      template <typename ConversionFactor>
      struct conversion_factor_normalise : pqs::detail::to_conversion_factor<
         typename pqs::detail::ll_conversion_factor_normalise<
            typename pqs::detail::to_ll_conversion_factor<ConversionFactor>::type
         >::type
      >{};
   }

   template <typename T> 
       requires pqs::is_conversion_factor<T>
   using normalise = typename impl::conversion_factor_normalise<std::remove_cvref_t<T> >::type;

   namespace impl{

      template <typename Lhs, typename Rhs>
        requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl< Lhs, pqs::divides, Rhs>{

         typedef typename pqs::detail::to_ll_conversion_factor<Lhs>::type ll_lhs_type;
         typedef typename pqs::detail::to_ll_conversion_factor<Rhs>::type ll_rhs_type;

         typedef typename pqs::detail::to_conversion_factor<
            typename pqs::detail::ll_conversion_factor_normalise<
               pqs::detail::ll_conversion_factor<
                  typename std::ratio_divide<
                     typename ll_lhs_type::multiplier,
                     typename ll_rhs_type::multiplier
                  >::type,
                  typename std::ratio_subtract<
                     typename ll_lhs_type::exponent,
                     typename ll_rhs_type::exponent
                  >::type
               >
            >::type
         >::type type;
      };

      template <typename CF>
         requires is_conversion_factor<CF>
      struct unary_op_impl<
         pqs::meta::reciprocal,
         CF
      > : binary_op<
            conversion_factor<
              std::ratio<1>, 
              exponent10<0> 
            >,
            pqs::divides,
            CF
      >{};


      template <typename Lhs, typename Rhs>
         requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl< Lhs, pqs::times, Rhs>{

         typedef typename pqs::detail::to_ll_conversion_factor<Lhs>::type ll_lhs_type;
         typedef typename pqs::detail::to_ll_conversion_factor<Rhs>::type ll_rhs_type;

         typedef typename pqs::detail::to_conversion_factor<
            typename pqs::detail::ll_conversion_factor_normalise<
               pqs::detail::ll_conversion_factor<
                  typename std::ratio_multiply<
                     typename ll_lhs_type::multiplier,
                     typename ll_rhs_type::multiplier
                  >::type,
                  typename std::ratio_add<
                     typename ll_lhs_type::exponent,
                     typename ll_rhs_type::exponent
                  >::type
               >
            >::type
         >::type type;
      };

      template <typename Lhs, typename Rhs>
         requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::plus, Rhs
      > : pqs::detail::to_conversion_factor<
               typename pqs::detail::ll_conversion_factor_add<
                  typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
                  typename pqs::detail::to_ll_conversion_factor<Rhs>::type
               >::type
         >{};

      // TODO conv_factor minus

      template <typename Lhs, typename Rhs>
      requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::less,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
            typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
            typename pqs::detail::to_ll_conversion_factor<Rhs>::type
        >::value < 0)>{};

      template <typename Lhs, typename Rhs>
            requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::less_equal,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
            typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
            typename pqs::detail::to_ll_conversion_factor<Rhs>::type
         >::value <= 0)>{};

      template <typename Lhs, typename Rhs>
            requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::equal_to,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
            typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
            typename pqs::detail::to_ll_conversion_factor<Rhs>::type
         >::value == 0)>{};

      template <typename Lhs, typename Rhs>
         requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::not_equal_to,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
            typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
            typename pqs::detail::to_ll_conversion_factor<Rhs>::type
         >::value != 0)>{};

      template <typename Lhs, typename Rhs>
         requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::greater_equal,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
          typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
          typename pqs::detail::to_ll_conversion_factor<Rhs>::type
      >::value >= 0)>{};

      template <typename Lhs, typename Rhs>
         requires is_conversion_factor<Lhs> && is_conversion_factor<Rhs>
      struct binary_op_impl<
         Lhs, pqs::greater,Rhs
      > : std::integral_constant<bool, (pqs::detail::ll_conversion_factor_compare<
         typename pqs::detail::to_ll_conversion_factor<Lhs>::type,
         typename pqs::detail::to_ll_conversion_factor<Rhs>::type
      >::value > 0)>{};

   } // impl

}//pqs

#endif // PQS_BITS_CONVERSION_FACTOR_OPS_HPP_INCLUDED
