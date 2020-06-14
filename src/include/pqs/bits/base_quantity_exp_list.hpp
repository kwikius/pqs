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

namespace pqs{ namespace meta{

   namespace impl{

      template <typename ... D>
      struct get_num_elements_impl<
         pqs::base_quantity_exp_list<D...>
      > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

      template <typename T>
      struct push_back_impl<pqs::base_quantity_exp_list<>,T >{
         typedef pqs::base_quantity_exp_list<T> type;
      };

      template <typename ... L, typename T>
      struct push_back_impl<pqs::base_quantity_exp_list<L...>,T >{
         typedef pqs::base_quantity_exp_list<L...,T> type;
      };

      template <typename Front, typename ... List>
      struct pop_front_impl<pqs::base_quantity_exp_list<Front,List...> >
      {
         typedef pqs::base_quantity_exp_list<List...> type;
      };

      template <>
      struct pop_front_impl<pqs::base_quantity_exp_list<> >
      {
         typedef pqs::undefined type;
      };

      template <typename...L, typename T>
      struct push_front_impl<pqs::base_quantity_exp_list<L...> , T>
      {
          typedef pqs::base_quantity_exp_list<T,L...> type;
      };

      template < typename Front, typename... List> 
      struct front_impl<pqs::base_quantity_exp_list<Front,List...> >
      {
         typedef Front type;
      };

      template < typename Front> 
      struct front_impl<pqs::base_quantity_exp_list<Front> >
      {
         typedef Front type;
      };

      template <>
      struct front_impl<pqs::base_quantity_exp_list<> >
      {
         // could just be empty_list?
         typedef pqs::undefined type;
      };

      template < typename Front ,typename... List> 
      struct back_impl< pqs::base_quantity_exp_list<Front,List...> >
      {
         typedef typename back_impl<pqs::base_quantity_exp_list<List...> >::type type;
      };

      template < typename Back> 
      struct back_impl< pqs::base_quantity_exp_list<Back> >
      {
         typedef Back type;
      };

      template <>
      struct back_impl<pqs::base_quantity_exp_list<> >
      {
         typedef pqs::undefined type;
      };

   }// impl

}}//pqs::meta


#endif // PQS_BITS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
