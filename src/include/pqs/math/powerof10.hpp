#ifndef PQS_MATH_POWEROF10_HPP_INCLUDED
#define PQS_MATH_POWEROF10_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <type_traits>
#include <pqs/math/to_power.hpp>

namespace pqs{ namespace impl{

   template <typename ValueType, typename Exp, typename Where = void>
   struct pow10_impl : pqs::undefined{};

   template <
      typename ValueType, // some numeric type
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      ValueType, Exp,
      typename pqs::where_< 
         pqs::meta::and_<
            std::integral_constant<bool,(Exp::den == 1)>,
            std::integral_constant<bool,(Exp::num == 0)>
         >
      >::type
   >{
        typedef ValueType type;
        static constexpr type value = static_cast<type>(1);
   };

   template <
      typename ValueType, // some numeric type
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      ValueType, Exp,
      typename pqs::where_< 
         pqs::meta::and_<
            std::is_integral<ValueType>,
            std::integral_constant<bool,(Exp::den == 1)>,
            std::integral_constant<bool,(Exp::num > 0)>,
            std::integral_constant<bool,(Exp::num <= std::numeric_limits<ValueType>::digits10)>
        >
      >::type
    >{
         typedef ValueType type;
         static constexpr type value = static_cast<type>(10) * pow10_impl< ValueType, std::ratio<Exp::num -1,1> >::value;
    };


   template <
      typename ValueType, // some numeric type
      typename Exp // std:ratio
   > 
   struct pow10_impl<
      ValueType, Exp,
      typename pqs::where_< 
         pqs::meta::or_<
            pqs::meta::not_<std::is_integral<ValueType> >,
            std::integral_constant<bool,(Exp::den !=1)>,
            std::integral_constant<bool,(Exp::num < 0)>,
            std::integral_constant<bool,(Exp::num > std::numeric_limits<ValueType>::digits10)>
        >
      >::type
    >{
         typedef pqs::real_type type;
         static constexpr type value = pqs::to_power<Exp::num,Exp::den>(static_cast<type>(10));
    };


}

   template <typename ValueType, typename Exp>
   struct powerof10 : impl::pow10_impl<ValueType,Exp>{};

}//pqs


#endif // PQS_MATH_POWEROF10_HPP_INCLUDED
