#ifndef PQS_META_NARROWEST_RUNTIME_TYPE_HPP_INCLUDED
#define PQS_META_NARROWEST_RUNTIME_TYPE_HPP_INCLUDED

#include <type_traits>
#include <cstdint>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/meta/eval_if.hpp>
#include <pqs/bits/config.hpp>
#include <pqs/bits/meta/identity.hpp>
#include <pqs/bits/meta/integer_max.hpp>

namespace pqs{ 
   namespace meta{
   namespace impl{
    
      template <typename T>
      struct narrowest_runtime_type_impl : pqs::undefined_arg<T>{};

      template <typename R>
         requires is_ratio<R>
      struct narrowest_runtime_type_impl<
         R
      > : pqs::meta::eval_if<
         std::integral_constant<bool,( R::den != 1)>,
            pqs::meta::identity<pqs::real_type>,
         std::integral_constant<bool,( R::num <= pqs::meta::integer_max<int8_t>::value)>,
            pqs::meta::identity<int8_t>,
         std::integral_constant<bool,( R::num <= pqs::meta::integer_max<int16_t>::value)>,
            pqs::meta::identity<int16_t>,
         std::integral_constant<bool,( R::num <= pqs::meta::integer_max<int32_t>::value)>,
            pqs::meta::identity<int32_t>,
         pqs::meta::identity<int64_t>
      >{};
     } //impl

      template <typename T>
      struct narrowest_runtime_type : impl::narrowest_runtime_type_impl<T>{};
  } //meta
}//pqs


#endif // PQS_META_NARROWEST_RUNTIME_TYPE_HPP_INCLUDED
