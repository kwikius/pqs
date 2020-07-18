#ifndef PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED
#define PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED

#include <type_traits>
#include <cstdint>

namespace pqs{ namespace meta{

  namespace impl{

     template <typename List,typename T, typename Where = void>
     struct push_back_impl;

     template <typename List,typename T, typename Where = void>
     struct push_front_impl;

     template <typename List, typename Where = void>
     struct get_num_elements_impl;

     template <typename List, typename Where = void>
     struct pop_front_impl;

     template <typename List,typename Where = void>
     struct pop_back_impl;

     template <typename List,typename Where = void>
     struct front_impl;

     template <typename List,typename Where = void>
     struct back_impl;

     template <uint32_t N, typename List, typename Where = void>
     struct at_impl;

     template <typename List, typename Where = void> 
     struct is_type_list_impl : std::false_type{};

   }

   template <typename List,typename T>
   struct push_back : impl::push_back_impl<List,T>{};

   template <typename List,typename T>
   using push_back_t = typename push_back<List,T>::type;

   template <typename List,typename T>
   struct push_front : impl::push_front_impl<List,T>{};
 
   template <typename List,typename T>
   using push_front_t = typename push_front<List,T>::type;

   template <typename List>
   struct get_num_elements : impl::get_num_elements_impl<List>{};

   template <typename List>
   inline constexpr uint32_t get_num_elements_v = get_num_elements<List>::value;

   template <typename List>
   struct pop_front : impl::pop_front_impl<List>{};

   template <typename List>
   using pop_front_t = typename pop_front<List>::type;

   template <typename List>
   struct pop_back : impl::pop_back_impl<List>{};

   template <typename List>
   using pop_back_t = typename pop_back<List>::type;

   template <typename List>
   struct front : impl::front_impl<List>{};

   template <typename List>
   using front_t = typename front<List>::type;

   template <typename List>
   struct back : impl::back_impl<List>{};

   template <typename List>
   using back_t = typename back<List>::type;

   template <uint32_t N, typename List>
   struct at : impl::at_impl<N,List>{};

   template <uint32_t N,typename List> 
   using at_t = typename at<N,List>::type;

}} // pqs::meta

#endif // PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED
