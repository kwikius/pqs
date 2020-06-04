#ifndef PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
#define PQS_BITS_DIMENSION_DEF_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/concepts/dimension.hpp>

namespace pqs{

   namespace detail {
      struct base_quantity_exp_list_base{};
   }

   // initially rename to base_quantity_exp_list
   // then convert to type_list<base_quantity_exp...>
   template <typename ...D>
   struct base_quantity_exp_list : pqs::detail::base_quantity_exp_list_base{
      typedef base_quantity_exp_list type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   // Probably not needed... 
   template <> struct base_quantity_exp_list<>{
      typedef base_quantity_exp_list type;
      static constexpr uint32_t num_elements = 0;
   };

   // rename to is_base_quantity_exp_list
   template <typename ... D >
   struct is_base_quantity_exp_list<pqs::base_quantity_exp_list<D...> > : std::true_type{};

   // refactor to is_named_dimension
   template <typename D>
   struct is_derived_dimension : 
      pqs::meta::and_<
         pqs::meta::not_<is_base_quantity_exp_list<D> >,
         std::is_base_of<pqs::detail::base_quantity_exp_list_base,D>
      >{};

}

#endif // PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
