#ifndef PQS_MATH_POWEROF10_HPP_INCLUDED
#define PQS_MATH_POWEROF10_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <type_traits>
#include <limits>
#include <pqs/math/fn_to_power.hpp>
#include <pqs/meta/identity.hpp>

namespace pqs{ namespace impl{

   template <typename Exp, typename Where = void>
   struct pow10_impl : pqs::undefined{};

   template <
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      Exp,
      typename pqs::where_< 
         pqs::meta::and_<
            std::integral_constant<bool,(Exp::den == 1)>,
            std::integral_constant<bool,(Exp::num == 0)>
         >
      >::type
   >{
        typedef int8_t type;
        static constexpr type value = static_cast<type>(1);
   };

   template <
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      Exp,
      typename pqs::where_< 
         pqs::meta::and_<
            std::integral_constant<bool,(Exp::den == 1)>,
            std::integral_constant<bool,(Exp::num > 0)>,
            std::integral_constant<bool,(Exp::num <= std::numeric_limits<int64_t>::digits10)>
         >
      >::type
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
      static constexpr type value = static_cast<type>(10) * pow10_impl<std::ratio<Exp::num -1,1> >::value;
   };


   template <
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      Exp,
      typename pqs::where_< 
         pqs::meta::or_<
            std::integral_constant<bool,(Exp::den !=1)>,
            std::integral_constant<bool,(Exp::num < 0)>,
            std::integral_constant<bool,(Exp::num > std::numeric_limits<int64_t>::digits10)>
        >
      >::type
    >{
         typedef pqs::real_type type;
         static constexpr type value = pqs::fn_to_power<Exp::num,Exp::den>(static_cast<type>(10));
    };

   } // impl

   template <typename Exp>
   struct powerof10 : impl::pow10_impl<Exp>{};

}//pqs


#endif // PQS_MATH_POWEROF10_HPP_INCLUDED
