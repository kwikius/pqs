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
#include <pqs/concepts/dimension.hpp>

namespace pqs{

   template <typename ...D>
   struct dimension{
      typedef dimension type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   // Probably not needed... 
   template <> struct dimension<>{
      typedef dimension type;
      static constexpr uint32_t num_elements = 0;
   };

   template <typename ... D >
   struct is_dimension<pqs::dimension<D...> > : std::true_type{};

   namespace impl{

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_<
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>, 
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : dimension<
            //typename pqs::add_base_quantity_exp<Lhs,Rhs>::type
            typename pqs::binary_op<Lhs,pqs::meta::plus,Rhs>::type
         >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_<
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>, 
               pqs::of_same_base_quantity<Lhs,Rhs>
            >
         >::type
      > : dimension<
          //  typename pqs::subtract_base_quantity_exp<Lhs,Rhs>::type
            typename pqs::binary_op<Lhs,pqs::meta::minus,Rhs>::type
         >{};

      // create a dimension of two base_dims
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
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
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>,
               pqs::is_base_quantity_exp<Rhs>, 
               meta::not_<pqs::of_same_base_quantity<Lhs,Rhs> >
            > 
         >::type
      > : dimension<
            Lhs,
           // typename pqs::negate_base_quantity_exp<Rhs>::type
            typename pqs::unary_op<pqs::meta::negate,Rhs>::type
         >{};


      // add to a dimension
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_dimension<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::add_dimensions<Lhs,pqs::dimension<Rhs> >{};

         // add to a dimension
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_dimension<Lhs>,
               pqs::is_base_quantity_exp<Rhs>
            > 
         >::type
      > : pqs::subtract_dimensions<Lhs,pqs::dimension<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_dimension<Rhs>
            > 
         >::type
      > : pqs::add_dimensions<pqs::dimension<Lhs>,Rhs >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_base_quantity_exp<Lhs>, 
               pqs::is_dimension<Rhs>
            > 
         >::type
      > : pqs::subtract_dimensions<pqs::dimension<Lhs>,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_dimension<Lhs>, 
               pqs::is_dimension<Rhs>
            > 
         >::type
      > : pqs::add_dimensions<Lhs,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               pqs::is_dimension<Lhs>, 
               pqs::is_dimension<Rhs>
            > 
         >::type
      > : pqs::subtract_dimensions<Lhs,Rhs>{};

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
            pqs::is_dimension<Lhs>,
            pqs::is_base_quantity_exp<Rhs>
         > ,
         pqs::meta::and_<
          pqs::is_base_quantity_exp<Lhs>, 
          pqs::is_dimension<Rhs>
         >, 
         pqs::meta::and_<
            pqs::is_dimension<Lhs>, 
            pqs::is_dimension<Rhs>
         > 
      >,  
      pqs::binary_op<Lhs,pqs::meta::times,Rhs>
   >::type
   operator * ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op<Lhs,pqs::meta::times,Rhs>::type{};
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
            pqs::is_dimension<Lhs>,
            pqs::is_base_quantity_exp<Rhs>
         > ,
         pqs::meta::and_<
          pqs::is_base_quantity_exp<Lhs>, 
          pqs::is_dimension<Rhs>
         >, 
         pqs::meta::and_<
            pqs::is_dimension<Lhs>, 
            pqs::is_dimension<Rhs>
         > 
      >,  
      pqs::binary_op<Lhs,pqs::meta::divides,Rhs>
   >::type
   operator / ( Lhs , Rhs ) 
   {
      return typename pqs::binary_op<Lhs,pqs::meta::divides,Rhs>::type{};
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
