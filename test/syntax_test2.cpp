
#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/base_dimension.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/binary_op_tags.hpp>

namespace pqs{

   template <typename Lhs, typename Op, typename Rhs, typename Where = void>
   struct binary_op_impl : pqs::undefined{};

   template <typename Lhs, typename Op, typename Rhs>
   struct binary_op : binary_op_impl<Lhs,Op,Rhs> {};

   // add base_dims -> to same base dim of higher extent
   template <typename Lhs, typename Rhs>
   struct binary_op_impl <
      Lhs,meta::times,Rhs,
      typename where_<detail::same_base_dimension<Lhs,Rhs> >::type
   >
   {
      typedef dimension<
         typename pqs::detail::add_base_dimension_ratio<Lhs,Rhs>::type
      > type;
   };

   template <typename Lhs, typename Rhs>
   struct binary_op_impl <
      Lhs,meta::divides,Rhs,
      typename where_<detail::same_base_dimension<Lhs,Rhs> >::type
   >
   {
      typedef dimension<
         typename pqs::detail::subtract_base_dimension_ratio<Lhs,Rhs>::type
      > type;
   };

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
   >
   {
      typedef typename pqs::dimension<Lhs,Rhs> type;
   };

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
   >
   {
      
      typedef typename pqs::dimension<Lhs,
         typename detail::negate_base_dimension_ratio<Rhs>::type
      > type;
   };


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

}

#include "make_quantity.hpp"

#include <pqs/length.hpp>

#include <iostream>

using namespace pqs;

namespace {

   constexpr dim_mass<1> mass_dim;
   constexpr dim_length<1> length_dim;
   constexpr dim_time<1> time_dim;

}

void make_quantity_test()
{
   // instantiate some quantity type
   auto constexpr q = make_quantity<3>(
      mass_dim,              // -> dim_mass<1> 
      length_dim,            // -> dim_length<1>
      time_dim * time_dim,   // -> dim_time<2>
      length_dim * time_dim, // -> dimension<dim_length<1>,dim_time<1> >
      dim_current<2>{},
      20.0  // -> value_type
   );


   auto constexpr q2 = make_quantity<-3>(
      mass_dim * length_dim / (time_dim * time_dim), 20.0
   );
    //########################################

       // COMPILE FAIL To get type in error message
   int x = q2;
}
/*
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp: In function ‘void make_quantity_test()’:
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp:242:12: error: cannot convert ‘const pqs::quantity<pqs::unit<-3, pqs::dimension<pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> > >, double>’ to ‘int’ in initialization
  242 |    int x = q2;
      |            ^~
      |            |
      |            const pqs::quantity<pqs::unit<-3, pqs::dimension<pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> > >, double>
Process terminated with status 1 (0 minute(s), 11 second(s))
1 error(s), 0 warning(s) (0 minute(s), 11 second(s))
*/



