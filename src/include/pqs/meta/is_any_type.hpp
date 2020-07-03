#ifndef QUAN_META_IS_ANY_TYPE_HPP_INCLUDED
#define QUAN_META_IS_ANY_TYPE_HPP_INCLUDED


#include <type_traits>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{ namespace meta{

   namespace impl{

      template <typename T, typename Where = void> 
      struct is_any_type_impl : std::true_type{};

      template <>
      struct is_any_type_impl<pqs::undefined> : std::false_type{};

      template <typename ... Args>
      struct is_any_type_impl<pqs::undefined_arg<Args...> > : std::false_type{};

   };

   template <typename T> 
   struct is_any_type : impl::is_any_type_impl< std::remove_cvref_t<T> >{};

 }} // quan::meta

#endif // QUAN_META_IS_ANY_TYPE_HPP_INCLUDED
