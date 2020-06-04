#ifndef PQS_DIMENSION_HPP_INCLUDED
#define PQS_DIMENSION_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/dimension_def.hpp>
#include <pqs/meta/merge_dim.hpp>
#include <pqs/meta/transform.hpp>
#include <pqs/meta/fold.hpp>
#include <pqs/bits/std_ratio.hpp>

namespace pqs{

   namespace impl{

      // create a dimension of two base_dims
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>, 
               meta::not_<pqs::of_same_base_quantity<Lhs,Rhs> >
            > 
         >::type
      > : dimension<Lhs,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>, 
               meta::not_<pqs::of_same_base_quantity<Lhs,Rhs> >
            > 
         >::type
      > : dimension<
            Lhs,
            typename pqs::unary_op<pqs::meta::reciprocal,Rhs>::type
         >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::times,pqs::dimension<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::dimension<Lhs>,pqs::times,Rhs>{};

         // add to a dimension
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::divides,pqs::dimension<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::dimension<Lhs>,pqs::divides,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::meta::merge_dim<Lhs,pqs::times,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::meta::merge_dim<Lhs,divides,Rhs>{};

      namespace detail{

         template<typename Ratio>
         struct to_power_impl{
            template <typename BaseQExp>
            struct apply : pqs::binary_op<BaseQExp,struct pqs::to_power,Ratio>{};
         };

         struct push_back_not_zero{
            
            template <typename List, typename Elem>
            struct apply : pqs::meta::eval_if<
               pqs::base_quantity_exp_is_zero<Elem>,
                  List,
               pqs::meta::push_back<List,Elem>
            >{};
         };
      }

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,struct pqs::to_power,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::impl::detail::is_std_ratio<Rhs>
            > 
         >::type
      > : pqs::meta::fold<
            typename pqs::meta::transform<
               typename pqs::meta::merge_sort<
                  Lhs,
                  pqs::meta::detail::base_quantity_exp_sort_fun
               >::type,
               pqs::dimension<>, 
               detail::to_power_impl<Rhs>
            >::type,
            pqs::dimension<>,
            detail::push_back_not_zero
         >{};

      template <typename D>
      struct unary_op_impl <
         pqs::meta::reciprocal,D,
         typename where_< 
            pqs::is_base_quantity_exp_list<D>
         >::type
      > : pqs::binary_op<D,struct pqs::to_power,std::ratio<-1> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::equal_to,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : std::is_same<
            typename pqs::meta::merge_dim<Lhs,divides,Rhs>::type,
            pqs::dimension<> 
      > {};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::not_equal_to,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::meta::not_<pqs::binary_op<Lhs,pqs::equal_to,Rhs> > {};
      
   } // impl
}// pqs
   
   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename pqs::eval_where<
      pqs::meta::or_<
         pqs::meta::and_<
            pqs::is_base_quantity_exp<Lhs>,
            pqs::is_base_quantity_exp<Rhs> 
         >,
         pqs::meta::and_<
            pqs::is_base_quantity_exp_list<Lhs>,
            pqs::is_base_quantity_exp<Rhs>
         > ,
         pqs::meta::and_<
            pqs::is_base_quantity_exp<Lhs>, 
            pqs::is_base_quantity_exp_list<Rhs>
         >, 
         pqs::meta::and_<
            pqs::is_base_quantity_exp_list<Lhs>, 
            pqs::is_base_quantity_exp_list<Rhs>
         > 
      >,  
      pqs::binary_op<Lhs,pqs::times,Rhs>
   >::type
   operator * ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op<Lhs,pqs::times,Rhs>::type{};
   }

   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename pqs::eval_where<
      pqs::meta::or_<
         pqs::meta::and_<
            pqs::is_base_quantity_exp<Lhs>,
            pqs::is_base_quantity_exp<Rhs> 
         >,
         pqs::meta::and_<
            pqs::is_base_quantity_exp_list<Lhs>,
            pqs::is_base_quantity_exp<Rhs>
         > ,
         pqs::meta::and_<
            pqs::is_base_quantity_exp<Lhs>, 
            pqs::is_base_quantity_exp_list<Rhs>
         >, 
         pqs::meta::and_<
            pqs::is_base_quantity_exp_list<Lhs>, 
            pqs::is_base_quantity_exp_list<Rhs>
         > 
      >,  
      pqs::binary_op<Lhs,pqs::divides,Rhs>
   >::type
   operator / ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op<Lhs,pqs::divides,Rhs>::type{};
   }

//} //pqs

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

#endif // PQS_DIMENSION_HPP_INCLUDED
