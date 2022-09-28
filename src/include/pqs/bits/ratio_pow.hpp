#ifndef PQS_BITS_RATIO_POW_HPP_INCLUDED
#define PQS_BITS_RATIO_POW_HPP_INCLUDED

#include <ratio>
#include <type_traits>
#include <cmath>

namespace pqs{

   template <typename Number>
      requires std::is_arithmetic_v<Number>
   constexpr int get_digits10( Number const & v_in)
   {
      //check number greater than 0
      int n = 0;
      auto v = v_in;
      for ( ; v >=Number{1};++n){
         v /= Number{10};
      }
      return n;
   }

   template <typename Number>
      requires std::is_floating_point_v<Number>
   constexpr int get_fractdigits10( Number const & v_in)
   {
      int n = 0;
      for (auto v = v_in; (v - std::floor(v) ) != Number{0} ;++n){
         v = (v - std::floor(v)) * 10;
      }
      return n;
   }

   namespace detail{

      template <typename Number>
         requires std::is_floating_point_v<decltype(Number::value)>
      constexpr auto to_rational()
      {
         int constexpr max_digits = std::numeric_limits<intmax_t>::digits10 ;
         long double constexpr number_value = Number::value ;

         int constexpr digits = get_digits10(number_value);
         static_assert(max_digits > digits);
         int constexpr max_fractdigits = max_digits - digits;
         // chop of smallest fraction
         int constexpr fractdigits = std::min(get_fractdigits10(number_value),max_fractdigits);
         intmax_t constexpr pow10digits10 = static_cast<intmax_t>(std::pow(10,fractdigits));
         intmax_t constexpr nume = static_cast<intmax_t>(number_value * pow10digits10 + 0.5);
         return typename std::ratio<nume,pow10digits10>::type{};
      }

      template <typename R, int N>
      struct float_rational_root{
         static constexpr double value =
            std::pow(static_cast<double>(R::num)/R::den,1./N);
      };

      template <typename Base,int Exp>
      struct ratio_root_impl {
         static_assert(Base::num >= 0);
         using type = decltype(detail::to_rational<
            detail::float_rational_root<Base,Exp>
         >());
      };

      template <typename Base>
      struct ratio_root_impl<Base,0> {
         using type = std::ratio<1>;
      };

      template <typename Base>
      struct ratio_root_impl<Base,1> {
         using type = typename Base::type;
      };

      template <int Exp>
      struct ratio_root_impl<std::ratio<1>,Exp> {
          using type = std::ratio<1>;
      };

      template <int D,int Exp>
         requires ( D != 1 && Exp > 1 )
      struct ratio_root_impl<std::ratio<1,D> ,Exp> {
         using type =
            std::ratio_divide<
               std::ratio<1>,
               typename ratio_root_impl<
                  std::ratio<D,1>,Exp
               >::type
            >;
      };

      template <typename Base, typename Exp>
      struct ratio_pow_impl {
         using type =
            typename ratio_root_impl<
               typename ratio_pow_impl<Base,std::ratio<Exp::num,1> >::type,
               Exp::den
            >::type;
      };

      template <intmax_t Bn, intmax_t Bd, intmax_t En>
         requires (En > 1)
      struct ratio_pow_impl<std::ratio<Bn,Bd>,std::ratio<En,1> >{
         using base_type = typename std::ratio<Bn,Bd>::type;
         using type =
            std::ratio_multiply<
               base_type,
               typename ratio_pow_impl<base_type,std::ratio<En-1,1> >::type
            >;
      };

      template <intmax_t Bn, intmax_t Bd, intmax_t En>
         requires (En < 0)
      struct ratio_pow_impl<std::ratio<Bn,Bd>,std::ratio<En,1> >{
         using base_type = typename std::ratio<Bn,Bd>::type;
         using type =
            std::ratio_divide<
               std::ratio<1>,
               typename ratio_pow_impl<base_type,std::ratio<-En,1> >::type
            >;
      };

      template <intmax_t Bn, intmax_t Bd, intmax_t D1>
      struct ratio_pow_impl<std::ratio<Bn,Bd>,std::ratio<0,D1> >{
         using type = std::ratio<1>;
      };

      template <intmax_t Bn, intmax_t Bd>
      struct ratio_pow_impl<std::ratio<Bn,Bd>,std::ratio<1,1> >{
         using type = typename std::ratio<Bn,Bd>::type;
      };

   } //detail

   template <typename B, typename E>
      requires (B::den > 0 ) && (B::num >= 0 ) && ( E::den > 0)
   using ratio_pow =
      typename pqs::detail::ratio_pow_impl<
         typename B::type,
         typename E::type
      >::type;
}//pqs


#endif // PQS_BITS_RATIO_POW_HPP_INCLUDED
