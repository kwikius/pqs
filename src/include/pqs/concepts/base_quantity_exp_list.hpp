#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/not.hpp>

namespace pqs{

   namespace detail {
      struct base_quantity_exp_list_base{};
   }

   template <typename D>
   struct is_base_quantity_exp_list : std::false_type{};

   template <typename T>
   struct is_derived_from_base_quantity_exp_list : 
      pqs::meta::and_<
         std::is_base_of<pqs::detail::base_quantity_exp_list_base,T>,
         pqs::meta::not_<is_base_quantity_exp_list<T> >
      >
   {};

} //pqs

#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
