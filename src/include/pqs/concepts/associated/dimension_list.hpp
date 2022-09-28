#ifndef PQS_CONCEPTS_ASSOCIATED_DIMENSION_LIST_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_DIMENSION_LIST_DEFINITION_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/concepts/base_quantity_exponent.hpp>
#include <pqs/concepts/associated/is_dimension_list.hpp>
#include <pqs/concepts/associated/is_custom_dimension.hpp>
#include <pqs/concepts/associated/get_simple_dimension.hpp>
#include <pqs/concepts/associated/dimensionless.hpp>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/concepts/associated/unary_op.hpp>
#include <pqs/bits/meta/and.hpp>
#include <pqs/bits/meta/or.hpp>
#include <pqs/bits/meta/not.hpp>
#include <pqs/bits/meta/merge_dim.hpp>
#include <pqs/bits/meta/transform.hpp>
#include <pqs/bits/meta/fold.hpp>
#include <pqs/bits/std_ratio.hpp>

namespace pqs{

   namespace detail {
      /**
       * @brief base class for detecting a dimension_list
      */
      struct dimension_list_base{};
   }// detail

  /**
   * @brief dimension_list definition
   */
   template <base_quantity_exponent ...D>
   struct dimension_list : pqs::detail::dimension_list_base{
      typedef dimension_list type;
      typedef type simple_dimension;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   namespace impl {

     /**
      * @brief simple dimension_list specialisation impl
      */
      template <base_quantity_exponent ... D >
      struct is_dimension_list_impl<pqs::dimension_list<D...> >
      : std::true_type{};

     /**
      * @brief custom dimension_list impl
      */
      template <typename T>
         requires ( std::is_base_of_v<pqs::detail::dimension_list_base,T> &&
         ! is_dimension_list<T> )
      inline constexpr bool is_custom_dimension_impl<T> = true;

      template <typename T>
         requires std::is_base_of_v<pqs::detail::dimension_list_base,T>
      struct get_simple_dimension_impl<T>{
         typedef typename T::simple_dimension type;
      };

   } // impl

   namespace meta{ namespace impl{

     /**
      * @brief fulfil dimensionlist type_list requirements - get_num_elements impl
      */
      template <typename ... D>
      struct get_num_elements_impl<
         pqs::dimension_list<D...>
      > : std::integral_constant<uint32_t, (sizeof...(D) )>{};

//     /**
//      * @brief fulfil dimensionlist type_list requirements - push_back on empty list impl
//      */
//      template <typename T>
//      struct push_back_impl<pqs::dimension_list<>,T >{
//         typedef pqs::dimension_list<T> type;
//      };

     /**
      * @brief fulfil dimensionlist type_list requirements -
      *  empty list push back dimensionless nop impl
      */
      template <>
      struct push_back_impl<pqs::dimension_list<>,pqs::dimensionless >{
         typedef pqs::dimension_list<> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - push_back impl
      */
      template <typename ... L, typename T>
      struct push_back_impl<pqs::dimension_list<L...>,T >{
         typedef pqs::dimension_list<L...,T> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - push_back dimensionless nop impl
      */

      template <typename ... L>
      struct push_back_impl<pqs::dimension_list<L...>,dimensionless >{
         typedef pqs::dimension_list<L...> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - pop-front impl
      */

      template <typename Front, typename ... List>
      struct pop_front_impl<pqs::dimension_list<Front,List...> >
      {
         typedef pqs::dimension_list<List...> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - pop_front on empty list impl
      */
      template <>
      struct pop_front_impl<pqs::dimension_list<> >
      {
         typedef pqs::dimensionless type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - push-front impl
      */
      template <typename...L, typename T>
      struct push_front_impl<pqs::dimension_list<L...> , T>
      {
         typedef pqs::dimension_list<T,L...> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - push-front dimensionless impl
      */
      template <typename...L>
      struct push_front_impl<pqs::dimension_list<L...> , dimensionless>
      {
         typedef pqs::dimension_list<L...> type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - front impl
      */
      template < typename Front, typename... List>
      struct front_impl<pqs::dimension_list<Front,List...> >
      {
         typedef Front type;
      };

     /**
      * @brief fulfil dimensionlist type_list requirements - front empty list impl
      */
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

   }}// meta::impl

   namespace impl{

      template <
         pqs::base_quantity_exponent Lhs,
         pqs::base_quantity_exponent Rhs
      > requires (! pqs::of_same_base_quantity<Lhs,Rhs>)
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

         template<typename Ratio>
         struct base_quantity_exp_to_power_impl{
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

      //base_exp_list * base_exp_list
      template <base_quantity_exponent... Lhs,base_quantity_exponent... Rhs>
      struct binary_op_impl <
         dimension_list<Lhs...>,pqs::times,dimension_list<Rhs...>
      > : pqs::impl::detail::extract_single_element_list<
            typename pqs::meta::merge_dim< dimension_list<Lhs...>,times,dimension_list<Rhs...> >::type
      >{};

//divide
      template <
         pqs::base_quantity_exponent Lhs,
         pqs::base_quantity_exponent Rhs
      > requires (!of_same_base_quantity<Lhs,Rhs>)
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

      template <pqs::base_quantity_exponent... D>
      struct unary_op_impl <
         pqs::meta::reciprocal,dimension_list<D...>
      > : pqs::binary_op<
         dimension_list<D...>,
         struct pqs::to_power,std::ratio<-1>
      >{};

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
            detail::base_quantity_exp_to_power_impl<Rhs>
         >::type,
         pqs::dimension_list<>,
         detail::push_back_not_zero
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

   } //impl

} //pqs

#endif // PQS_CONCEPTS_ASSOCIATED_DIMENSION_LIST_DEFINITION_HPP_INCLUDED
