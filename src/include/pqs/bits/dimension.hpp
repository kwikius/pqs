#ifndef PQS_DIMENSION_HPP_INCLUDED
#define PQS_DIMENSION_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/dimension_def.hpp>
#include <pqs/meta/merge_dim.hpp>
#include <pqs/meta/transform.hpp>
#include <pqs/meta/fold.hpp>
#include <pqs/bits/std_ratio.hpp>

namespace pqs{

   namespace impl{

//multiply
      // base_exp * base_exp
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
      > : base_quantity_exp_list<Lhs,Rhs>{};

      // base_exp list * base-exp
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::times,pqs::base_quantity_exp_list<Rhs> >{};

      // base_exp * base_exp_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::base_quantity_exp_list<Lhs>,pqs::times,Rhs>{};

      namespace detail{

         template <typename List>
         struct extract_single_element_list{
            typedef List type;
         };

         template <typename Elem>
         struct extract_single_element_list<pqs::base_quantity_exp_list<Elem> >{
            typedef Elem type;
         };

      }

      //base_exp_list * base_exp_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > {
        // convert single element list to base_quantity_exp
         typedef typename pqs::impl::detail::extract_single_element_list<
            typename pqs::meta::merge_dim<Lhs,times,Rhs>::type
         >::type type;
      };

      // derived_dim * derived_dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_derived_dimension<Lhs>, 
               pqs::is_derived_dimension<Rhs>
            > 
         >::type
      > : pqs::binary_op<
         typename Lhs::base_exponent_type,
         pqs::times, 
         typename Rhs::base_exponent_type
      >{};

      // dim * derived_dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_dimension<Rhs>,
               pqs::is_derived_dimension<Lhs>, 
               pqs::meta::not_<pqs::is_derived_dimension<Rhs> >
            > 
         >::type
       > : pqs::binary_op<
         typename Lhs::base_exponent_type,
         pqs::times,
         Rhs
       >{};

      // derived_dim * dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_dimension<Lhs>,
               pqs::is_derived_dimension<Rhs>, 
               pqs::meta::not_<pqs::is_derived_dimension<Lhs> >
            > 
         >::type
       > : pqs::binary_op<
         Lhs,
         pqs::times,
         typename Rhs::base_exponent_type
      >{};

//divide
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
      > : base_quantity_exp_list<
          Lhs,
          typename pqs::unary_op<pqs::meta::reciprocal,Rhs>::type
      >{};
         // add to a base_quantity_exp_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::divides,pqs::base_quantity_exp_list<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::base_quantity_exp_list<Lhs>,pqs::divides,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_list<Lhs>, 
               pqs::is_base_quantity_exp_list<Rhs>
            > 
         >::type
      >{
         // convert single element list to base_quantity_exp
         typedef typename pqs::impl::detail::extract_single_element_list<
            typename pqs::meta::merge_dim<Lhs,divides,Rhs>::type
         >::type type;
      };

      // derived_dim / derived_dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_derived_dimension<Lhs>, 
               pqs::is_derived_dimension<Rhs>
            > 
         >::type
      > : pqs::binary_op<
         typename Lhs::base_exponent_type,
         pqs::divides, 
         typename Rhs::base_exponent_type
      >{};

      // dim / derived_dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_dimension<Rhs>,
               pqs::is_derived_dimension<Lhs>, 
               pqs::meta::not_<pqs::is_derived_dimension<Rhs> >
            > 
         >::type
       > : pqs::binary_op<
         typename Lhs::base_exponent_type,
         pqs::divides,
         Rhs
       >{};

      // derived_dim / dim
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_<  
            meta::and_<
               pqs::is_dimension<Lhs>,
               pqs::is_derived_dimension<Rhs>, 
               pqs::meta::not_<pqs::is_derived_dimension<Lhs> >
            > 
         >::type
       > : pqs::binary_op<
         Lhs,
         pqs::divides,
         typename Rhs::base_exponent_type
      >{};

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
// Note : the version for base_quantity_exp is defined in concepts/base_quantity_exp
// TODO refactor list versions to list enad base_quantity_exp to separate headers
  // only combos here
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
            pqs::base_quantity_exp_list<>, 
            detail::to_power_impl<Rhs>
         >::type,
         pqs::base_quantity_exp_list<>,
         detail::push_back_not_zero
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,
         struct pqs::to_power,
         Rhs,
         typename where_< 
            pqs::meta::and_<
               pqs::is_derived_dimension<Lhs>, 
               pqs::impl::detail::is_std_ratio<Rhs>
            > 
         >::type
      > : pqs::binary_op<typename Lhs::base_exponent_type,
            struct pqs::to_power,
            Rhs
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
            pqs::base_quantity_exp_list<> 
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

   
   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename pqs::eval_where<
      pqs::meta::and_<
         pqs::is_dimension<Lhs>,
         pqs::is_dimension<Rhs>
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
      pqs::meta::and_<
         pqs::is_dimension<Lhs>,
         pqs::is_dimension<Rhs>
      >, 
      pqs::binary_op<Lhs,pqs::divides,Rhs>
   >::type
   operator / ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op<Lhs,pqs::divides,Rhs>::type{};
   }

   template <int N, int D, typename Dim>
   inline
   constexpr
   typename pqs::eval_where<
         pqs::is_dimension<Dim>,
      pqs::binary_op<Dim,struct pqs::to_power,std::ratio<N,D> >
    >::type
    pow( Dim )
    {
        return typename pqs::binary_op<Dim,struct pqs::to_power,std::ratio<N,D>>::type{};
    }
//} //pqs

}// pqs

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

#endif // PQS_DIMENSION_HPP_INCLUDED
