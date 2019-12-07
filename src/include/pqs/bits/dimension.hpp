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
      static constexpr uint32_t num_elements = 0;
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
/*
   namespace impl{

       template <typename ... D>
       struct get_num_elements_impl<
            pqs::dimension<D...>
       > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

   }
*/
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
namespace quan{ namespace meta{

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
*/
namespace pqs{ namespace detail{

   // algorthim to extract the base_dimension from the dimension D
   template <typename D, base_dimension_id_t Id, int Size>
   struct get_base_dimension_i;

   // end of dimension D, base_dim not found so return zero size base_dim
   template <typename D, base_dimension_id_t Id>
   struct get_base_dimension_i<D,Id,0> : make_base_dimension_ratio<Id, std::ratio<0,1> >{};

   // not end of dimension D
   // return base_dim recursively
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

   //ll interfce to extract the base_dim with id Id from dimension D
   // base_dim of zero extent signifies not found
   template <typename D, base_dimension_id_t Id>
   struct get_base_dimension : get_base_dimension_i<
      D, Id,D::type::num_elements
   >{};

}} // pqs::detail

namespace pqs{ namespace detail{

/*
   find the base dimensions with id in lhs and rhs 
   apply Op and if result not zero add to result dimension
   Op is  Op<base_dimension,base_dimension> -> base_dimension
*/
   template <
      typename LhsD,  
      template <typename, typename> class Op,
      typename RhsD, 
      base_dimension_id_t Id,
      typename ResultD      
   >struct result_push_back_additive_op_dims_base_dims{

       typedef typename Op< 
          typename get_base_dimension<LhsD,Id>::type,
          typename get_base_dimension<RhsD,Id>::type
       >::type result_base_dim;

       typedef typename quan::meta::eval_if_c<
          base_dimension_is_zero<result_base_dim>::value,
          ResultD,
          quan::meta::push_back<ResultD,result_base_dim>
       >::type type;
   };

   // specialise above for addition
   template <
      typename LhsD,    
      typename RhsD, 
      base_dimension_id_t Id,
      typename ResultD
   >
   struct result_push_back_add_dims_base_dims :
   result_push_back_additive_op_dims_base_dims<
      LhsD, add_base_dimension_ratio, RhsD,Id, ResultD
   >{};

   // specialise above for subtraction
   template <
      typename LhsD,    
      typename RhsD, 
      base_dimension_id_t Id,
      typename ResultD
   >
   struct result_push_back_subtract_dims_base_dims :
   result_push_back_additive_op_dims_base_dims<
      LhsD,subtract_base_dimension_ratio, RhsD, Id, ResultD
   >{};

   // ll additive binary ops on dimensions
   // Op is  Op<base_dimension,base_dimension> -> base_dimension
   template < typename LhsD,template<typename,typename> class Op, typename RhsD, base_dimension_id_t I, typename ResultD>
   struct additive_op_dimensions_i{
      typedef typename result_push_back_additive_op_dims_base_dims<LhsD,Op,RhsD,I,ResultD>::type result;
      typedef typename quan::meta::eval_if_c<
         I == base_dimension_id_t::last_element,
         result,
         additive_op_dimensions_i<LhsD,Op,RhsD,static_cast<base_dimension_id_t>(static_cast<uint8_t>(I)+1),result>
      >::type type;
   };
 
   //Op is  Op<base_dimension,base_dimension> -> base_dimension
   template <typename LhsD, template<typename,typename> class Op,typename RhsD>
   struct additive_op_dimensions : additive_op_dimensions_i<LhsD,Op,RhsD,base_dimension_id_t::first_element, dimension<> >{};

   // ll additive ops on dimensions interface
   template <typename LhsD, typename RhsD>
   struct add_dimensions : additive_op_dimensions_i<LhsD,add_base_dimension_ratio, RhsD, base_dimension_id_t::first_element,dimension<> >{};

   template <typename LhsD, typename RhsD>
   struct subtract_dimensions : additive_op_dimensions_i<LhsD,subtract_base_dimension_ratio, RhsD, base_dimension_id_t::first_element,dimension<> >{};
       
}} // pqs::detail

#endif // PQS_DIMENSION_HPP_INCLUDED
