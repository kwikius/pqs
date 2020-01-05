#ifndef PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/strip_cr.hpp>

/*
   pqs_concept::quantity
   pqs::quantity_concept
   pqs::quantity

*/

namespace pqs{

   namespace impl{
      template <typename T, typename Where = void>
      struct is_quantity_impl : std::false_type{};

      template <typename T, typename Where = void>
      struct is_quantity_value_type_impl : std::false_type{};

      template <typename T>
      struct is_quantity_value_type_impl< 
         T, typename pqs::where_<std::is_arithmetic<T> >::type
      > : std::true_type{};

   }// impl

   template <typename T>
   struct is_quantity : impl::is_quantity_impl<typename pqs::meta::strip_cr<T>::type>{};

   template <typename T>
   struct is_quantity_value_type : impl::is_quantity_value_type_impl<typename pqs::meta::strip_cr<T>::type>{};

}// pqs


#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
