#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED2
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED2

#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/meta/merge_dim.hpp>
#include <pqs/meta/transform.hpp>
#include <pqs/meta/fold.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/types/dimensionless.hpp>

namespace pqs{

   namespace detail {
      struct dimension_list_base{};
   }

   namespace impl {

      template <typename D>
      struct is_simple_dimension_list_impl : std::false_type{};

   }

   template <typename D>
   struct is_simple_dimension_list_legacy : impl::is_simple_dimension_list_impl<
      typename pqs::meta::strip_cr<D>::type
   >{};

#if defined  __cpp_inline_variables
   template <typename D>
   inline constexpr bool is_simple_dimension_list = is_simple_dimension_list_legacy<D>::value;
#endif

   namespace impl{

      template <typename T>
      struct is_custom_dimension_list_impl : 
         pqs::meta::and_<
            std::is_base_of<pqs::detail::dimension_list_base,T>,
            pqs::meta::not_<is_simple_dimension_list_legacy<T> >
         >
      {};
   }

   template <typename T>
   struct is_custom_dimension_list_legacy : impl::is_custom_dimension_list_impl<
      typename pqs::meta::strip_cr<T>::type
   >{};

#if defined  __cpp_inline_variables

   template<typename T>
   inline constexpr bool is_custom_dimension_list = is_custom_dimension_list_legacy<T>::value;

#endif

   template <typename ...D>
   struct dimension_list : pqs::detail::dimension_list_base{
      typedef dimension_list type;
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   template <> struct dimension_list<>{
      typedef dimension_list type;
      typedef type base_exponent_type;
      static constexpr uint32_t num_elements = 0;
   };
   
   namespace impl {

      template <typename ... D >
      struct is_simple_dimension_list_impl<pqs::dimension_list<D...> > : std::true_type{};

      template <typename D>
      struct is_custom_dimension_impl : pqs::meta::or_<
         is_custom_dimension_list_legacy<D>,
         is_custom_base_quantity_exp_legacy<D>
      >{};
   }

   template <typename D>
   struct is_custom_dimension_legacy : impl::is_custom_dimension_impl<
      typename pqs::meta::strip_cr<D>::type
   >{};

#if defined  __cpp_inline_variables

   template <typename D>
   inline constexpr bool is_custom_dimension = is_custom_dimension_legacy<D>::value;

#endif

}// pqs

namespace pqs{ namespace meta{

   namespace impl{

      template <typename ... D>
      struct get_num_elements_impl<
         pqs::dimension_list<D...>
      > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

      template <typename T>
      struct push_back_impl<pqs::dimension_list<>,T >{
         typedef pqs::dimension_list<T> type;
      };

      template <typename ... L, typename T>
      struct push_back_impl<pqs::dimension_list<L...>,T >{
         typedef pqs::dimension_list<L...,T> type;
      };

      template <typename Front, typename ... List>
      struct pop_front_impl<pqs::dimension_list<Front,List...> >
      {
         typedef pqs::dimension_list<List...> type;
      };

      template <>
      struct pop_front_impl<pqs::dimension_list<> >
      {
         typedef pqs::undefined type;
      };

      template <typename...L, typename T>
      struct push_front_impl<pqs::dimension_list<L...> , T>
      {
          typedef pqs::dimension_list<T,L...> type;
      };

      template < typename Front, typename... List> 
      struct front_impl<pqs::dimension_list<Front,List...> >
      {
         typedef Front type;
      };

      template < typename Front> 
      struct front_impl<pqs::dimension_list<Front> >
      {
         typedef Front type;
      };

      template <>
      struct front_impl<pqs::dimension_list<> >
      {
         // could just be empty_list?
         typedef pqs::undefined type;
      };

      template < typename Front ,typename... List> 
      struct back_impl< pqs::dimension_list<Front,List...> >
      {
         typedef typename back_impl<pqs::dimension_list<List...> >::type type;
      };

      template < typename Back> 
      struct back_impl< pqs::dimension_list<Back> >
      {
         typedef Back type;
      };

      template <>
      struct back_impl<pqs::dimension_list<> >
      {
         typedef pqs::undefined type;
      };

   }// impl

}}//pqs::meta

namespace pqs{

   template <typename T>
   struct is_dimension_legacy : pqs::meta::or_<
      pqs::is_base_quantity_exp_legacy<T>,
      pqs::is_simple_dimension_list_legacy<T>,
      pqs::is_custom_dimension_legacy<T>
   >{};

   namespace impl{

//multiply
      // base_exp * base_exp
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_legacy<Lhs>,
               pqs::is_base_quantity_exp_legacy<Rhs>, 
               meta::not_<pqs::of_same_base_quantity_legacy<Lhs,Rhs> >
            > 
         >::type
      > : dimension_list<Lhs,Rhs>{};

      // base_exp list * base-exp
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>,
               pqs::is_base_quantity_exp_legacy<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::times,pqs::dimension_list<Rhs> >{};

      // base_exp * base_exp_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::dimension_list<Lhs>,pqs::times,Rhs>{};

      namespace detail{

         template <typename List>
         struct extract_single_element_list{
            typedef List type;
         };

         template <typename Elem>
         struct extract_single_element_list<pqs::dimension_list<Elem> >{
            typedef Elem type;
         };

         template <>
         struct extract_single_element_list<pqs::dimension_list<> >{
            typedef dimensionless type;
         };

      }

      //base_exp_list * base_exp_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
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
               pqs::is_custom_dimension_legacy<Lhs>, 
               pqs::is_custom_dimension_legacy<Rhs>
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
               pqs::is_dimension_legacy<Rhs>,
               pqs::is_custom_dimension_legacy<Lhs>, 
               pqs::meta::not_<pqs::is_custom_dimension_legacy<Rhs> >
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
               pqs::is_dimension_legacy<Lhs>,
               pqs::is_custom_dimension_legacy<Rhs>, 
               pqs::meta::not_<pqs::is_custom_dimension_legacy<Lhs> >
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
               pqs::is_base_quantity_exp_legacy<Lhs>,
               pqs::is_base_quantity_exp_legacy<Rhs>, 
               meta::not_<pqs::of_same_base_quantity_legacy<Lhs,Rhs> >
            > 
         >::type
      > : dimension_list<
          Lhs,
          typename pqs::unary_op<pqs::meta::reciprocal,Rhs>::type
      >{};
         // add to a dimension_list
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>,
               pqs::is_base_quantity_exp_legacy<Rhs>
            > 
         >::type
      > : pqs::binary_op<Lhs,pqs::divides,pqs::dimension_list<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
            > 
         >::type
      > : pqs::binary_op<pqs::dimension_list<Lhs>,pqs::divides,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
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
               pqs::is_custom_dimension_legacy<Lhs>, 
               pqs::is_custom_dimension_legacy<Rhs>
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
               pqs::is_dimension_legacy<Rhs>,
               pqs::is_custom_dimension_legacy<Lhs>, 
               pqs::meta::not_<pqs::is_custom_dimension_legacy<Rhs> >
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
               pqs::is_dimension_legacy<Lhs>,
               pqs::is_custom_dimension_legacy<Rhs>, 
               pqs::meta::not_<pqs::is_custom_dimension_legacy<Lhs> >
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
               pqs::base_quantity_exp_is_zero_legacy<Elem>,
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
               pqs::is_simple_dimension_list_legacy<Lhs>, 
               pqs::impl::detail::is_std_ratio<Rhs>
            > 
         >::type
      > : pqs::meta::fold<
         typename pqs::meta::transform<
            typename pqs::meta::merge_sort<
               Lhs,
               pqs::meta::detail::base_quantity_exp_sort_fun
            >::type,
            pqs::dimension_list<>, 
            detail::to_power_impl<Rhs>
         >::type,
         pqs::dimension_list<>,
         detail::push_back_not_zero
      >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,
         struct pqs::to_power,
         Rhs,
         typename where_< 
            pqs::meta::and_<
               pqs::is_custom_dimension_legacy<Lhs>, 
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
            pqs::is_simple_dimension_list_legacy<D>
         >::type
      > : pqs::binary_op<D,struct pqs::to_power,std::ratio<-1> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::equal_to,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
            > 
         >::type
      > : std::is_same<
            typename pqs::meta::merge_dim<Lhs,divides,Rhs>::type,
            pqs::dimension_list<> 
      > {};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,pqs::not_equal_to,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_simple_dimension_list_legacy<Lhs>, 
               pqs::is_simple_dimension_list_legacy<Rhs>
            > 
         >::type
      > : pqs::meta::not_<pqs::binary_op<Lhs,pqs::equal_to,Rhs> > {};
      
   } // impl

   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename pqs::eval_where<
      pqs::meta::and_<
         pqs::is_dimension_legacy<Lhs>,
         pqs::is_dimension_legacy<Rhs>
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
         pqs::is_dimension_legacy<Lhs>,
         pqs::is_dimension_legacy<Rhs>
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
         pqs::is_dimension_legacy<Dim>,
      pqs::binary_op<Dim,struct pqs::to_power,std::ratio<N,D> >
    >::type
    pow( Dim )
    {
       return typename pqs::binary_op<Dim,struct pqs::to_power,std::ratio<N,D>>::type{};
    }

}// pqs


#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
