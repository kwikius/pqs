#ifndef PQS_META_NARROWEST_INT_HPP_INCLUDED
#define PQS_META_NARROWEST_INT_HPP_INCLUDED

#include <pqs/bits/meta/eval_if.hpp>
#include <limits>

/// udl value impl
namespace pqs::meta::detail{
   /**
    * return type of min sized int that can hold V
    * narrowest_int
   **/
   template <unsigned long long V>
   struct narrowest_int_impl{
      typedef typename meta::eval_if<
            std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int8_t>::max()))>,
         meta::identity<int8_t>,
            std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int16_t>::max()))>,
         meta::identity<int16_t>,
            std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int32_t>::max()))>,
         meta::identity<int32_t>,
            std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int64_t>::max()))>,
         meta::identity<int64_t>,
         pqs::undefined
      >::type type;
   };
}// pqs::meta::detail

namespace pqs::meta{

   template <unsigned long long V>
   using narrowest_int = typename pqs::meta::detail::narrowest_int_impl<V>::type;
}

#endif // PQS_META_NARROWEST_INT_HPP_INCLUDED
