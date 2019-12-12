#ifndef PQS_DIMENSION_HPP_INCLUDED
#define PQS_DIMENSION_HPP_INCLUDED

#include <type_traits>

#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/meta/eval_if_else.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/base_dimension.hpp>
#include <pqs/meta/not.hpp>

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

   namespace detail{

      template <typename D>
      struct is_dimension : std::false_type{};

      template <typename ... D >
      struct is_dimension<pqs::dimension<D...> > : std::true_type{};

   }// detail
   
}// pqs

namespace pqs{ namespace meta{

   namespace impl{

      template <typename ... D>
      struct get_num_elements_impl<
         pqs::dimension<D...>
      > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

      template <typename T>
      struct push_back_impl<pqs::dimension<>,T >{
         typedef pqs::dimension<T> type;
      };

      template <typename ... L, typename T>
      struct push_back_impl<pqs::dimension<L...>,T >{
         typedef pqs::dimension<L...,T> type;
      };

      template <typename Front, typename ... List>
      struct pop_front_impl<pqs::dimension<Front,List...> >
      {
         typedef pqs::dimension<List...> type;
      };

      template <>
      struct pop_front_impl<pqs::dimension<> >
      {
         typedef pqs::undefined type;
      };

      template <typename...L, typename T>
      struct push_front_impl<pqs::dimension<L...> , T>
      {
          typedef pqs::dimension<T,L...> type;
      };

      template < typename Front, typename... List> 
      struct front_impl<pqs::dimension<Front,List...> >
      {
         typedef Front type;
      };

      template < typename Front> 
      struct front_impl<pqs::dimension<Front> >
      {
         typedef Front type;
      };

      template <>
      struct front_impl<pqs::dimension<> >
      {
         // could just be empty_list?
         typedef pqs::undefined type;
      };

      template < typename Front ,typename... List> 
      struct back_impl< pqs::dimension<Front,List...> >
      {
         typedef typename back_impl<pqs::dimension<List...> >::type type;
      };

      template < typename Back> 
      struct back_impl< pqs::dimension<Back> >
      {
         typedef Back type;
      };

      template <>
      struct back_impl<pqs::dimension<> >
      {
         typedef pqs::undefined type;
      };

   }// impl

}}//pqs::meta

/*
not reqd atm
namespace pqs{ namespace meta{ namespace impl{

   template <uint32_t N, typename... List>
   struct at_impl<N,pqs::dimension<List...> >{
       typedef pqs::dimension<List...> list_type;
       static_assert(N < list_type::length,"index out of range in pqs::dimension");
       typedef typename pqs::meta::eval_if_else_c<
            N==0,
            pqs::meta::front_impl<list_type>,
            pqs::meta::at<N-1,typename pqs::meta::pop_front<list_type>::type>
       >::type type; 
   };

   template <uint32_t N>
   struct at<N,pqs::dimension<> >{
      typedef pqs::undefined type;
   };
   
}}}// pqs::meta::impl
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
   typedef typename pqs::meta::front<dimension>::type base_dim;
   typedef typename pqs::meta::eval_if_else_c<
      (base_dim::base_dimension_id == Id),
      make_base_dimension_ratio<Id,typename base_dim::ratio>, // reduce
      get_base_dimension_i<pqs::meta::pop_front<dimension>,Id,Size - 1>
   >::type type;   
   };

   //ll interface to extract the base_dim with id Id from dimension D
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

       typedef typename pqs::meta::eval_if_else_c<
          base_dimension_is_zero<result_base_dim>::value,
          ResultD,
          pqs::meta::push_back<ResultD,result_base_dim>
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
      typedef typename pqs::meta::eval_if_else_c<
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

// -- multiplicative ops on dimension----
//  MultiplicativeOp<base_dim, Ratio> -> base_dim

   template <
      typename LhsD,  
      template <typename, typename> class MultiplicativeOp,
      typename Ratio, 
      base_dimension_id_t Id,
      typename ResultD      
   >struct result_push_back_multiplicative_op_dims_base_dims{

       typedef typename MultiplicativeOp< 
          typename get_base_dimension<LhsD,Id>::type,
          typename Ratio::type
       >::type result_base_dim;

       typedef typename pqs::meta::eval_if_else_c<
          base_dimension_is_zero<result_base_dim>::value,
          ResultD,
          pqs::meta::push_back<ResultD,result_base_dim>
       >::type type;
   };

   template <
      typename LhsD,    
      typename Ratio, 
      base_dimension_id_t Id,
      typename ResultD
   >
   struct result_push_back_multiply_dims_base_dims :
   result_push_back_multiplicative_op_dims_base_dims<
      LhsD, multiply_base_dimension_ratio, Ratio,Id, ResultD
   >{};

   template <
      typename LhsD,    
      typename Ratio, 
      base_dimension_id_t Id,
      typename ResultD
   >
   struct result_push_back_divide_dims_base_dims :
   result_push_back_multiplicative_op_dims_base_dims<
      LhsD, divide_base_dimension_ratio, Ratio,Id, ResultD
   >{};

     // Op is  Op<base_dimension,base_dimension> -> base_dimension
   template < typename LhsD,template<typename,typename> class Op, typename Ratio, base_dimension_id_t I, typename ResultD>
   struct multiplicative_op_dimensions_i{
      typedef typename result_push_back_multiplicative_op_dims_base_dims<LhsD,Op,Ratio,I,ResultD>::type result;
      typedef typename pqs::meta::eval_if_else_c<
         I == base_dimension_id_t::last_element,
         result,
         multiplicative_op_dimensions_i<LhsD,Op,Ratio,static_cast<base_dimension_id_t>(static_cast<uint8_t>(I)+1),result>
      >::type type;
   };

   template <typename LhsD, template<typename,typename> class Op,typename Ratio>
   struct multiplicative_op_dimensions : additive_op_dimensions_i<LhsD,Op,Ratio,base_dimension_id_t::first_element, dimension<> >{};

   // ll multiplicative ops on dimensions interface
   template <typename LhsD, typename Ratio>
   struct multiply_dimension : multiplicative_op_dimensions_i<LhsD,multiply_base_dimension_ratio, Ratio, base_dimension_id_t::first_element,dimension<> >{};

     // ll multiplicative ops on dimensions interface
   template <typename LhsD, typename Ratio>
   struct divide_dimension : multiplicative_op_dimensions_i<LhsD,divide_base_dimension_ratio, Ratio, base_dimension_id_t::first_element,dimension<> >{};

   // negate dimension

   template <typename D>
   struct negate_dimension : multiply_dimension<D,std::ratio<-1> >{};

  // compare

   template <typename DL, typename DR> 
   struct are_equal_dimensions : std::is_same<typename subtract_dimensions<DL,DR>::type, pqs::dimension<> >{}; 
  
   template <typename DL, typename DR> 
   struct are_not_equal_dimensions : meta::not_< are_equal_dimensions<DL,DR> >{};
       
}} // pqs::detail

#endif // PQS_DIMENSION_HPP_INCLUDED
