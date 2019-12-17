#ifndef PQS_CONCEPTS_RATIO_HPP_INCLUDED
#define PQS_CONCEPTS_RATIO_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_ratio_impl : std::false_type{};

   } // impl

   template <typename T>
   struct is_ratio : pqs::impl::is_ratio_impl<typename pqs::meta::strip_cr<T>::type>{};

} // pqs

#endif // PQS_CONCEPTS_RATIO_HPP_INCLUDED
