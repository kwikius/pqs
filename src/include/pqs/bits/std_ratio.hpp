#ifndef PQS_BITS_STD_RATIO_HPP_INCLUDED1
#define PQS_BITS_STD_RATIO_HPP_INCLUDED1

#include <ratio>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/concepts/associated/unary_op.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      struct is_ratio_impl : std::false_type{};

   } // impl

   template <typename T>
   inline constexpr bool is_ratio = pqs::impl::is_ratio_impl<
      std::remove_cvref_t<T> 
   >::value;

} // pqs

namespace pqs::detail{

   template <typename Ratio>
   struct std_ratio_abs{
      typedef typename std::ratio< 
         ((Ratio::num < 0)?-Ratio::num:Ratio::num)
        ,((Ratio::den < 0)?-Ratio::den:Ratio::den)
      >::type type;
   };

} // pqs::detail

namespace pqs::impl{

     template< intmax_t N, intmax_t D>
     struct is_ratio_impl<std::ratio<N,D> > : std::true_type{};

      template <typename T>
         requires is_ratio<T>
      struct unary_op_impl<
         pqs::meta::abs, T
      > : pqs::detail::std_ratio_abs<T>{};

      template <typename T>
         requires is_ratio<T>
      struct unary_op_impl<
         pqs::meta::negate, T
      > : std::ratio_subtract< std::ratio<0>,T >{};

      template <typename T>
          requires is_ratio<T>
      struct unary_op_impl<
         pqs::meta::reciprocal, T
      > : std::ratio_divide<std::ratio<1>, T >{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::plus, R
      > : std::ratio_add<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::minus, R
      > : std::ratio_subtract<L,R>{};

      template<typename L, typename R>
          requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::times, R
      > : std::ratio_multiply<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::divides, R
      > : std::ratio_divide<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::less, R
      > : std::ratio_less<L,R>{};


      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::equal_to, R
      > : std::ratio_equal<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::not_equal_to, R
      > : std::ratio_not_equal<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::greater_equal, R
      > : std::ratio_greater_equal<L,R>{};

      template<typename L, typename R>
         requires is_ratio<L> && is_ratio<R>
      struct binary_op_impl<
        L, pqs::greater, R
      > : std::ratio_greater<L,R>{};

} // pqs::impl

#endif // PQS_BITS_STD_RATIO_HPP_INCLUDED
