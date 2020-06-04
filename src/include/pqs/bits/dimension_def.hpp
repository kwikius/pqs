#ifndef PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
#define PQS_BITS_DIMENSION_DEF_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
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
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   // Probably not needed... 
   template <> struct base_quantity_exp_list<>{
      typedef base_quantity_exp_list type;
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = 0;
   };

   // rename to is_base_quantity_exp_list
   template <typename ... D >
   struct is_base_quantity_exp_list<pqs::base_quantity_exp_list<D...> > : std::true_type{};

   template <typename T>
   struct is_derived_from_base_quantity_exp_list : 
      pqs::meta::and_<
         std::is_base_of<pqs::detail::base_quantity_exp_list_base,T>,
         pqs::meta::not_<is_base_quantity_exp_list<T> >
      >
   {};

   // TODO also derived from base_quantity_exp
   template <typename D>
   struct is_derived_dimension : pqs::meta::or_<
      is_derived_from_base_quantity_exp_list<D>,
      is_derived_from_base_quantity_exp<D>
   >{};

   template <typename T>
   struct is_dimension : pqs::meta::or_<
      pqs::is_base_quantity_exp<T>,
      pqs::is_base_quantity_exp_list<T>,
      pqs::is_derived_dimension<T>
   >{};

}

#endif // PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
