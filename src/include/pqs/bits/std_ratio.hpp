#ifndef PQS_BITS_STD_RATIO_HPP_INCLUDED1
#define PQS_BITS_STD_RATIO_HPP_INCLUDED1

//#include <pqs/concepts/ratio.hpp>
#include <ratio>
#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_ratio_impl : std::false_type{};

   } // impl

   template <typename T>
   struct is_ratio : pqs::impl::is_ratio_impl< std::remove_cvref_t<T> >{};

} // pqs

namespace pqs{namespace detail{

   template <typename Ratio>
   struct std_ratio_abs{
      typedef typename std::ratio< 
         ((Ratio::num < 0)?-Ratio::num:Ratio::num)
        ,((Ratio::den < 0)?-Ratio::den:Ratio::den)
      >::type type;
   };

}} // pqs::detail

namespace pqs{ namespace impl{

     template< intmax_t N, intmax_t D>
     struct is_ratio_impl<std::ratio<N,D> > : std::true_type{};

      namespace detail{

         template <typename T>
         struct is_std_ratio : std::false_type{};

         template <intmax_t N, intmax_t D>
         struct is_std_ratio<std::ratio<N,D> > : std::true_type{};

      }

      template <typename T>
      struct unary_op_impl<
         pqs::meta::abs,
         T,
         typename pqs::where_< pqs::impl::detail::is_std_ratio<T> >::type
      > : pqs::detail::std_ratio_abs<T>{};

      template <typename T>
      struct unary_op_impl<
         pqs::meta::negate,
         T,
         typename pqs::where_< pqs::impl::detail::is_std_ratio<T> >::type
      > : std::ratio_subtract< std::ratio<0>,T >{};

      template <typename T>
      struct unary_op_impl<
         pqs::meta::reciprocal,
         T,
         typename pqs::where_< pqs::impl::detail::is_std_ratio<T> >::type
      > : std::ratio_divide<std::ratio<1>, T >{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::plus, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_add<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::minus, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_subtract<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::times, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_multiply<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::divides, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_divide<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::less, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_less<L,R>{};


      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::equal_to, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_equal<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::not_equal_to, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_not_equal<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::greater_equal, R,
        typename pqs::where_<
           pqs::meta::and_<
            pqs::impl::detail::is_std_ratio<L>,
            pqs::impl::detail::is_std_ratio<R>
         >
        >::type
      > : std::ratio_greater_equal<L,R>{};

      template<typename L, typename R>
      struct binary_op_impl<
        L, pqs::greater, R,
        typename pqs::where_<
           pqs::meta::and_<
              pqs::impl::detail::is_std_ratio<L>,
              pqs::impl::detail::is_std_ratio<R>
           >
        >::type
      > : std::ratio_greater<L,R>{};

}} // pqs::impl

#endif // PQS_BITS_STD_RATIO_HPP_INCLUDED
