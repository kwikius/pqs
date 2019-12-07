#ifndef PQS_DIMENSION_HPP_INCLUDED
#define PQS_DIMENSION_HPP_INCLUDED

#include <quan/meta/type_sequence.hpp>
#include <type_traits>

namespace pqs{

   template <typename ...D>
   struct dimension{
       typedef dimension type;
       static constexpr uint32_t num_elements = sizeof...(D);
   };

   template <> struct dimension<>{
      typedef dimension type;
      static constexpr uint32_t length = 0;
   };

}
/*
namespace quan{ namespace impl{

   // 
   template <typename ...D>
      struct is_model_of_impl<
         quan::meta::TypeSequence_,
         pqs::dimension<D...> 
      > : std::true_type{};

}} // quan::impl
*/
namespace quan{ namespace meta{

   namespace impl{

       template <typename ... D>
       struct get_num_elements_impl<
            pqs::dimension<D...>
       > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

   }

   template <typename T>
   struct push_back<pqs::dimension<>,T >{
      typedef pqs::dimension<T> type;
   };

   template <typename ... L, typename T>
   struct push_back<pqs::dimension<L...>,T >{
      typedef pqs::dimension<L...,T> type;
   };

   template <typename Front, typename ... List>
   struct pop_front<pqs::dimension<Front,List...> >
   {
      typedef pqs::dimension<List...> type;
   };

   template <>
   struct pop_front<pqs::dimension<> >
   {
      // could just be empty_list?
      typedef quan::undefined type;
   };

   template <typename...L, typename T>
   struct push_front<pqs::dimension<L...> , T>
   {
       typedef pqs::dimension<T,L...> type;
   };

   template < typename Front, typename... List> 
   struct front<pqs::dimension<Front,List...> >
   {
      typedef Front type;
   };

   template < typename Front> 
   struct front<pqs::dimension<Front> >
   {
      typedef Front type;
   };

   template <>
   struct front<pqs::dimension<> >
   {
      // could just be empty_list?
      typedef quan::undefined type;
   };

   template < typename Front ,typename... List> 
   struct back< pqs::dimension<Front,List...> >
   {
      typedef typename back<pqs::dimension<List...> >::type type;
   };

   template < typename Back> 
   struct back< pqs::dimension<Back> >
   {
      typedef Back type;
   };

   template <>
   struct back<pqs::dimension<> >
   {
      // could just be empty_list?
      typedef quan::undefined type;
   };

}}//quan::meta
/*
namespace pqs {
   namespace detail {

      template <uint32_t N,typename List, typename other_list = pqs::dimension<> >
      struct dimension_get_first_n{
         
         typedef typename quan::meta::front<List>::type first_type;
         typedef typename quan::meta::pop_front<List>::type rest_type;
         typedef typename quan::meta::push_back<other_list,first_type>::type result_list_type;
         typedef typename quan::meta::eval_if_c<
            result_list_type::length == N,
            result_list_type,
            dimension_get_first_n<N,rest_type,result_list_type>
         >::type type;
      };
   }//detail
}// pqs
*/
namespace quan{ namespace meta{

/*
   template<typename... List>
   struct pop_back<pqs::dimension<List...> >{
      typedef pqs::dimension<List...> list_type;
      typedef typename pqs::detail::dimension_get_first_n<list_type::length-1,list_type>::type type;
   };

   template< typename Last>
   struct pop_back<pqs::dimension<Last> >{
       typedef pqs::dimension<> type;
   };

   template <>
   struct pop_back<pqs::dimension<> >
   {
      typedef quan::undefined type;
   };
*/
   template <uint32_t N, typename... List>
   struct at<N,pqs::dimension<List...> >{
       typedef pqs::dimension<List...> list_type;
       static_assert(N < list_type::length,"index out of range in pqs::dimension");
       typedef typename quan::meta::eval_if_c<
            N==0,
            quan::meta::front<list_type>,
            quan::meta::at<N-1,typename quan::meta::pop_front<list_type>::type>
       >::type type; 
   };

   template <uint32_t N>
   struct at<N,pqs::dimension<> >{
      typedef quan::undefined type;
   };
   
}}// quan::meta

namespace pqs{ namespace detail{

   // algorthim to extract the base_dimension from the dimension
   template <typename D, base_dimension_id_t Id, int Size>
   struct get_base_dimension_i;

   // zero base_dim is same as not found
   template <typename D, base_dimension_id_t Id>
   struct get_base_dimension_i<D,Id,0> : make_base_dimension_ratio<Id, std::ratio<0,1> >{};

   template <typename D, base_dimension_id_t Id, int Size>
   struct get_base_dimension_i {
   typedef typename D::type dimension;
   typedef typename quan::meta::front<dimension>::type base_dim;
   typedef typename quan::meta::eval_if_c<
      (base_dim::base_dimension_id == Id),
      make_base_dimension_ratio<Id,typename base_dim::ratio>, // reduce
      get_base_dimension_i<quan::meta::pop_front<dimension>,Id,Size - 1>
   >::type type;   
   };

   template <typename D, base_dimension_id_t Id>
   struct get_base_dimension : get_base_dimension_i<
      D, Id,quan::meta::get_num_elements<typename D::type>::value
   >{};

}} // pqs::detail

#endif // PQS_DIMENSION_HPP_INCLUDED
