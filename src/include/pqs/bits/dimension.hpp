#ifndef PQS_DIMENSION_HPP_INCLUDED
#define PQS_DIMENSION_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/bits/binary_op.hpp>

#include <pqs/bits/dimension_impl.hpp>

namespace pqs{

   namespace impl{
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_<detail::same_base_dimension<Lhs,Rhs> >::type
      > : dimension<
            typename pqs::detail::add_base_dimension_ratio<Lhs,Rhs>::type
         >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_<detail::same_base_dimension<Lhs,Rhs> >::type
      > : dimension<
            typename pqs::detail::subtract_base_dimension_ratio<Lhs,Rhs>::type
         >{};

      // create a dimension of two base_dims
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               detail::is_base_dimension_ratio<Lhs>,
               detail::is_base_dimension_ratio<Rhs>, 
               meta::not_<detail::same_base_dimension<Lhs,Rhs> >
            > 
         >::type
      > : dimension<Lhs,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               detail::is_base_dimension_ratio<Lhs>,
               detail::is_base_dimension_ratio<Rhs>, 
               meta::not_<detail::same_base_dimension<Lhs,Rhs> >
            > 
         >::type
      > : dimension<Lhs,
            typename detail::negate_base_dimension_ratio<Rhs>::type
         >{};


      // add to a dimension
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               detail::is_dimension<Lhs>,
               detail::is_base_dimension_ratio<Rhs>
            > 
         >::type
      > : pqs::detail::add_dimensions<Lhs,pqs::dimension<Rhs> >{};

         // add to a dimension
      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               detail::is_dimension<Lhs>,
               detail::is_base_dimension_ratio<Rhs>
            > 
         >::type
      > : pqs::detail::subtract_dimensions<Lhs,pqs::dimension<Rhs> >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               detail::is_base_dimension_ratio<Lhs>, 
               detail::is_dimension<Rhs>
            > 
         >::type
      > : pqs::detail::add_dimensions<pqs::dimension<Lhs>,Rhs >{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               detail::is_base_dimension_ratio<Lhs>, 
               detail::is_dimension<Rhs>
            > 
         >::type
      > : pqs::detail::subtract_dimensions<pqs::dimension<Lhs>,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::times,Rhs,
         typename where_< 
            meta::and_<
               detail::is_dimension<Lhs>, 
               detail::is_dimension<Rhs>
            > 
         >::type
      > : pqs::detail::add_dimensions<Lhs,Rhs>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl <
         Lhs,meta::divides,Rhs,
         typename where_< 
            meta::and_<
               detail::is_dimension<Lhs>, 
               detail::is_dimension<Rhs>
            > 
         >::type
      > : pqs::detail::subtract_dimensions<Lhs,Rhs>{};

   }
   

   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename eval_where<
      meta::or_<
         meta::and_<
           detail::is_base_dimension_ratio<Lhs>,
           detail::is_base_dimension_ratio<Rhs> 
         >,
         meta::and_<
            detail::is_dimension<Lhs>,
            detail::is_base_dimension_ratio<Rhs>
         > ,
         meta::and_<
          detail::is_base_dimension_ratio<Lhs>, 
          detail::is_dimension<Rhs>
         >, 
         meta::and_<
            detail::is_dimension<Lhs>, 
            detail::is_dimension<Rhs>
         > 
      >,  
      binary_op<Lhs,meta::times,Rhs>
   >::type
   operator * ( Lhs , Rhs ) 
   {
      return typename binary_op<Lhs,pqs::meta::times,Rhs>::type{};
   }

   template <typename Lhs, typename Rhs>
   inline
   constexpr
   typename eval_where<
      meta::or_<
         meta::and_<
           detail::is_base_dimension_ratio<Lhs>,
           detail::is_base_dimension_ratio<Rhs> 
         >,
         meta::and_<
            detail::is_dimension<Lhs>,
            detail::is_base_dimension_ratio<Rhs>
         > ,
         meta::and_<
          detail::is_base_dimension_ratio<Lhs>, 
          detail::is_dimension<Rhs>
         >, 
         meta::and_<
            detail::is_dimension<Lhs>, 
            detail::is_dimension<Rhs>
         > 
      >,  
      binary_op<Lhs,meta::divides,Rhs>
   >::type
   operator / ( Lhs , Rhs ) 
   {
      return typename binary_op<Lhs,pqs::meta::divides,Rhs>::type{};
   }

} // pqs

#endif // PQS_DIMENSION_HPP_INCLUDED
