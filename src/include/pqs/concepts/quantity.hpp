#ifndef PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};
   }// impl

   template <typename T>
   struct is_quantity : impl::is_quantity_impl<typename pqs::meta::strip_cr<T>::type>{};

}// pqs


#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
