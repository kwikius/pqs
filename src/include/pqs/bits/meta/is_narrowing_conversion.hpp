#ifndef PQS_META_IS_NARROWING_CONVERSION_HPP_INCLUDED
#define PQS_META_IS_NARROWING_CONVERSION_HPP_INCLUDED

#pragma once

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/bits/meta/and.hpp>
#include <pqs/bits/meta/not.hpp>
#include <pqs/bits/meta/strip_cr.hpp>

namespace pqs { namespace meta{

   namespace impl{

      template <typename From, typename To, typename Where = void>
      struct is_narrowing_conversion_impl : std::false_type {};

      template <typename From, typename To>
      struct is_narrowing_conversion_impl<
         From,
         To,
         typename pqs::where_<
            pqs::meta::and_<
               std::is_arithmetic<From>,
               std::is_arithmetic<To>,
               pqs::meta::not_<
                  std::is_same<typename std::common_type<From, To>::type, To>
               >
            >
         >::type
      > : std::true_type {};

   }//impl

   template <typename From, typename To>
   inline constexpr bool is_narrowing_conversion = 
      impl::is_narrowing_conversion_impl<
      std::remove_cvref_t<From>,
      std::remove_cvref_t<To>
   >::value;

}} //pqs::meta

#endif // PQS_META_IS_NARROWING_CONVERSION_HPP_INCLUDED
