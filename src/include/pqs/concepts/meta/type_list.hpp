#ifndef PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED
#define PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED

#include <type_traits>
#include <cstdint>

namespace pqs { namespace concepts { namespace meta{

   struct type_list;

}}}

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
  struct push_front : impl::push_front_impl<List,T>{}; ;

  template <typename List>
  struct get_num_elements : impl::get_num_elements_impl<List>{};

  template <typename List>
  struct pop_front : impl::pop_front_impl<List>{};

  template <typename List>
  struct pop_back : impl::pop_back_impl<List>{};

  template <typename List>
  struct front : impl::front_impl<List>{};

  template <typename List>
  struct back : impl::back_impl<List>{};

  template <uint32_t N, typename List>
  struct at : impl::at_impl<N,List>{};

}} // pqs::meta

#endif // PQS_CONCEPTS_META_TYPE_LIST_HPP_INCLUDED
