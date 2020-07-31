#ifndef PQS_MATH_POWEROF10_HPP_INCLUDED
#define PQS_MATH_POWEROF10_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/bits/undefined.hpp>
#include <type_traits>
#include <limits>
#include <pqs/bits/math/fn_to_power.hpp>
#include <pqs/bits/meta/identity.hpp>

namespace pqs{ namespace impl{

   template <typename Exp>
   struct pow10_impl : pqs::undefined{};

   template < typename Exp>
      requires (Exp::den == 1) && (Exp::num == 0)
   struct pow10_impl<
      Exp
   >{
        typedef int8_t type;
        static constexpr type value = static_cast<type>(1);
   };

   template <
      typename Exp // std:ratio
   > 
      requires 
         (Exp::den == 1) && (Exp::num > 0) &&
         (Exp::num <= std::numeric_limits<int64_t>::digits10)
   struct pow10_impl<
      Exp
   >{
      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(Exp::num <= std::numeric_limits<int8_t>::digits10 )>,
            pqs::meta::identity<int8_t>,
         std::integral_constant<bool,(Exp::num <= std::numeric_limits<int16_t>::digits10 )>,
            pqs::meta::identity<int16_t>,
         std::integral_constant<bool,(Exp::num <= std::numeric_limits<int32_t>::digits10 )>,
            pqs::meta::identity<int32_t>,
         pqs::meta::identity<int64_t>
      >::type type;
      static constexpr type value = 
         static_cast<type>(10) * pow10_impl<std::ratio<Exp::num -1,1> >::value;
   };


   template <
      typename Exp // std:ratio
   > 
      requires (Exp::den != 1) || (Exp::num < 0) ||
      (Exp::num > std::numeric_limits<int64_t>::digits10)
   struct pow10_impl<
      Exp
    >{
         typedef pqs::real_type type;
         static constexpr type value = 
            pqs::fn_to_power<Exp::num,Exp::den>(static_cast<type>(10));
    };

   } // impl

   template <typename Exp>
   struct powerof10 : impl::pow10_impl<Exp>{};

}//pqs


#endif // PQS_MATH_POWEROF10_HPP_INCLUDED
