#ifndef PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED2
#define PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED2

#include <type_traits>
#include <pqs/bits/meta/and.hpp>
#include <pqs/bits/meta/not.hpp>
#include <pqs/bits/meta/or.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/bits/meta/merge_dim.hpp>
#include <pqs/bits/meta/transform.hpp>
#include <pqs/bits/meta/fold.hpp>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/associated/get_simple_dimension.hpp>
#include <pqs/concepts/base_quantity_exponent.hpp>
#include <pqs/types/dimensionless.hpp>

namespace pqs{

   namespace detail {
      struct dimension_list_base{};
   }

   template <base_quantity_exponent ...D>
   struct dimension_list : pqs::detail::dimension_list_base{
      typedef dimension_list type;
      typedef type simple_dimension;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   template <> struct dimension_list<>{
      typedef dimension_list type;
      typedef type simple_dimension;
      static constexpr uint32_t num_elements = 0;
   };

   namespace impl {

      template <typename D>
      struct is_simple_dimension_list_impl : std::false_type{};

      template <base_quantity_exponent ... D >
      struct is_simple_dimension_list_impl<pqs::dimension_list<D...> > 
      : std::true_type{};
   }

   template <typename D>
   inline constexpr bool is_simple_dimension_list 
      = impl::is_simple_dimension_list_impl< std::remove_cvref_t<D> >::value;

   namespace impl{

      template <typename T>
      inline constexpr bool is_custom_dimension_list_impl =
         std::is_base_of_v<pqs::detail::dimension_list_base,T> &&
         ! is_simple_dimension_list<T>
         ;

   }

   template<typename T>
   inline constexpr bool is_custom_dimension_list =
      impl::is_custom_dimension_list_impl<std::remove_cvref_t<T> >;

   namespace impl {

      template <typename D>
      inline constexpr bool is_custom_dimension_impl  =
         is_custom_dimension_list<D> || 
         is_custom_base_quantity_exp<D>
      ;
   }

   template <typename D>
   inline constexpr bool is_custom_dimension =
      impl::is_custom_dimension_impl<typename std::remove_cvref_t<D> >;

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

      template <>
      struct push_back_impl<pqs::dimension_list<>,pqs::dimensionless >{
         typedef pqs::dimension_list<> type;
      };

      template <typename ... L, typename T>
      struct push_back_impl<pqs::dimension_list<L...>,T >{
         typedef pqs::dimension_list<L...,T> type;
      };

      template <typename ... L>
      struct push_back_impl<pqs::dimension_list<L...>,dimensionless >{
         typedef pqs::dimension_list<L...> type;
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

      template <typename...L>
      struct push_front_impl<pqs::dimension_list<L...> , dimensionless>
      {
          typedef pqs::dimension_list<L...> type;
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
         typedef pqs::dimensionless type;
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
         typedef pqs::dimensionless type;
      };
   }// impl

}}//pqs::meta

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_dimension_impl =
        is_base_quantity_exponent<T> || 
        is_simple_dimension_list<T> ||
        is_custom_dimension<T>;
 
   } // impl

   template <typename T>
   inline constexpr bool is_dimension = 
      impl::is_dimension_impl< std::remove_cvref_t<T> >;

   template <typename T>
   concept dimension = is_dimension<T>;

   namespace impl{

      template <pqs::dimension D>
      struct get_simple_dimension_impl<D>{
         typedef typename D::simple_dimension type;
      };
   }

   namespace impl{

      template <
         pqs::base_quantity_exponent Lhs, 
         pqs::base_quantity_exponent Rhs
      > requires ! pqs::of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
      > : pqs::meta::merge_sort<
          dimension_list<Lhs,Rhs>,
          pqs::meta::detail::base_quantity_exp_sort_fun
      >{};

      // base_exp list * base-exp
      template <base_quantity_exponent... Lhs, base_quantity_exponent Rhs>
      struct binary_op_impl <
         dimension_list<Lhs...>, pqs::times, Rhs
      > : pqs::binary_op<dimension_list<Lhs...>,pqs::times, pqs::dimension_list<Rhs> >{};

      // base_exp * base_exp_list
      template <base_quantity_exponent Lhs, base_quantity_exponent... Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,dimension_list<Rhs...>
      > : pqs::binary_op<pqs::dimension_list<Lhs>,pqs::times,dimension_list<Rhs...> >{};

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
      template <base_quantity_exponent... Lhs,base_quantity_exponent... Rhs>
      struct binary_op_impl <
         dimension_list<Lhs...>,pqs::times,dimension_list<Rhs...>

      > : pqs::impl::detail::extract_single_element_list<
            typename pqs::meta::merge_dim< dimension_list<Lhs...>,times,dimension_list<Rhs...> >::type
      >{ };

      // derived_dim * derived_dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            pqs::is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
      > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::times, 
         get_simple_dimension<Rhs>
      >{};

      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            pqs::is_custom_dimension<Lhs> &&
            ! pqs::is_custom_dimension<Rhs> 
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
      > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::times,
         Rhs
       >{};

      // derived_dim * dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            ! is_custom_dimension<Lhs> &&
            is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::times,Rhs
       > : pqs::binary_op<
         Lhs,
         pqs::times,
         get_simple_dimension<Rhs>
      >{};

//divide
      template <
         pqs::base_quantity_exponent Lhs, 
         pqs::base_quantity_exponent Rhs
      > requires !of_same_base_quantity<Lhs,Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
      > : pqs::meta::merge_sort<
          dimension_list<Lhs,typename pqs::unary_op<pqs::meta::reciprocal,Rhs>::type>,
          pqs::meta::detail::base_quantity_exp_sort_fun
      >{};

         // add to a dimension_list
      template <
         pqs::base_quantity_exponent... Lhs, 
         pqs::base_quantity_exponent Rhs
      >
      struct binary_op_impl <
         pqs::dimension_list<Lhs...>,pqs::divides,Rhs
      > : pqs::binary_op<
            pqs::dimension_list<Lhs...>,
            pqs::divides,pqs::dimension_list<Rhs> 
      >{};

      template <
         pqs::base_quantity_exponent Lhs, 
         pqs::base_quantity_exponent... Rhs
      >
      struct binary_op_impl <
         Lhs,pqs::divides,pqs::dimension_list<Rhs...>
      > : pqs::binary_op<
         pqs::dimension_list<Lhs>,
         pqs::divides,
         pqs::dimension_list<Rhs...>
      >{};

      template <
         pqs::base_quantity_exponent... Lhs, 
         pqs::base_quantity_exponent... Rhs
      >
      struct binary_op_impl <
         pqs::dimension_list<Lhs...>,
         pqs::divides,
         pqs::dimension_list<Rhs...>
      > : pqs::impl::detail::extract_single_element_list<
            typename pqs::meta::merge_dim<
               pqs::dimension_list<Lhs...>,
               divides,
               pqs::dimension_list<Rhs...> 
            >::type
         >{};

      // derived_dim / derived_dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            pqs::is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
      > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::divides, 
         get_simple_dimension<Rhs>
      >{};

      // dim / derived_dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            ! pqs::is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
       > : pqs::binary_op<
         get_simple_dimension<Lhs>,
         pqs::divides,
         Rhs
       >{};

      // derived_dim / dim
      template <pqs::dimension Lhs, pqs::dimension Rhs>
         requires
            ! pqs::is_custom_dimension<Lhs> &&
              is_custom_dimension<Rhs>
      struct binary_op_impl <
         Lhs,pqs::divides,Rhs
       > : pqs::binary_op<
         Lhs,
         pqs::divides,
         get_simple_dimension<Rhs>
      >{};

      namespace detail{

         template<typename Ratio>
         struct to_power_impl{
            template <typename BaseQExp>
            struct apply : pqs::binary_op<BaseQExp,struct pqs::to_power,Ratio>{};
         };

         struct push_back_not_zero{
            
            template <typename List, typename Elem>
            struct apply : pqs::meta::eval_if_c<
               pqs::base_quantity_exp_is_zero<Elem>,
               List,
               pqs::meta::push_back<List,Elem>
            >{};
         };
      }

      template <pqs::base_quantity_exponent... Lhs, typename Rhs>
         requires pqs::is_ratio<Rhs>
      struct binary_op_impl <
         dimension_list<Lhs...>,struct pqs::to_power,Rhs
      > : pqs::meta::fold<
         typename pqs::meta::transform<
            typename pqs::meta::merge_sort<
               dimension_list<Lhs...>,
               pqs::meta::detail::base_quantity_exp_sort_fun
            >::type,
            pqs::dimension_list<>, 
            detail::to_power_impl<Rhs>
         >::type,
         pqs::dimension_list<>,
         detail::push_back_not_zero
      >{};

      template <pqs::dimension Lhs, typename Rhs>
         requires 
            pqs::is_custom_dimension<Lhs> &&
            pqs::is_ratio<Rhs>
      struct binary_op_impl <
         Lhs,
         struct pqs::to_power,
         Rhs
      > : pqs::binary_op<
            get_simple_dimension<Lhs>,
            struct pqs::to_power,
            Rhs
      >{};
      
      template <pqs::base_quantity_exponent... D>
      struct unary_op_impl <
         pqs::meta::reciprocal,dimension_list<D...>
      > : pqs::binary_op<
         dimension_list<D...>,
         struct pqs::to_power,std::ratio<-1> 
      >{};

      template <
         pqs::base_quantity_exponent... Lhs,    
         pqs::base_quantity_exponent... Rhs
      >
      struct binary_op_impl <
         dimension_list<Lhs...>,pqs::equal_to,dimension_list<Rhs...>
      > : std::is_same<
         typename pqs::meta::merge_dim<
            dimension_list<Lhs...>,
            divides,
            dimension_list<Rhs...>
            >::type,
            pqs::dimension_list<> 
      > {};

      template <typename... Lhs, typename... Rhs>
      struct binary_op_impl <
         dimension_list<Lhs...>,
         pqs::not_equal_to, 
         dimension_list<Rhs...>
      > : pqs::meta::not_<
         pqs::binary_op<
            dimension_list<Lhs...>,
            pqs::equal_to,
            dimension_list<Rhs...>
         >
      > {};
   } // impl

   template <pqs::dimension Lhs, pqs::dimension Rhs>
   inline
   constexpr
   auto
   operator * ( Lhs , Rhs ) 
   {
      return pqs::binary_op_t<Lhs,pqs::times,Rhs>{};
   }

   template <pqs::dimension Lhs, pqs::dimension Rhs>
   inline constexpr
   auto operator / ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op_t<Lhs,pqs::divides,Rhs>{};
   }

   template <int N, int D, pqs::dimension Dim>
      requires ( D != 0)
   inline constexpr
   auto  pow( Dim )
   {
       return pqs::binary_op_t<Dim,struct pqs::to_power,std::ratio<N,D> >{};
   }

   template <int N, pqs::dimension Dim>
   inline constexpr
   auto  pow( Dim )
   {
      return pqs::binary_op_t<Dim,struct pqs::to_power,std::ratio<N,1> >{};
   }

}// pqs


#endif // PQS_CONCEPTS_BASE_QUANTITY_EXP_LIST_HPP_INCLUDED
