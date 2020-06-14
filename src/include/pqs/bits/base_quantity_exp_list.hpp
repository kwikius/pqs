#ifndef PQS_BITS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
#define PQS_BITS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/concepts/base_quantity_exp_list.hpp>

namespace pqs{

   // eventually convert to type_list<base_quantity_exp...>
   template <typename ...D>
   struct base_quantity_exp_list : pqs::detail::base_quantity_exp_list_base{
      typedef base_quantity_exp_list type;
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   template <> struct base_quantity_exp_list<>{
      typedef base_quantity_exp_list type;
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = 0;
   };

   template <typename ... D >
   struct is_base_quantity_exp_list<pqs::base_quantity_exp_list<D...> > : std::true_type{};



} // pqs


#endif // PQS_BITS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
