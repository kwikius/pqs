
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

namespace pqs{

     template <int Exp, typename List>
     using make_unit = typename detail::make_unit<Exp,List>::type;
}

void make_quantity_test()
{

   auto constexpr q2 = make_quantity<-3>(
      mass_dim * length_dim / (time_dim * time_dim), 20.0
   );
   
   // alternative form
   auto q3 = quantity<
     make_unit<
       -3,
       decltype(mass_dim * length_dim / (time_dim * time_dim))
     >,
     double
   >{20.0};

   q3 = q2; // check structural equality


   // COMPILE FAIL To get type in error message
  // int x = q2;
}
/*

-------------- Build: Quan in std_units (compiler: GNU GCC-9 Compiler)---------------

g++-9 -std=c++2a -fconcepts -Wno-literal-suffix -Wno-non-template-friend -Wno-stringop-overflow -Wno-pedantic -I/home/andy/cpp/projects/std_units/pqs/src/include -I/home/andy/cpp/projects/quan-trunk -c /home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp -o obj/Debug/pqs/test/syntax_test2.o
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp: In function ‘void make_quantity_test()’:
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp:232:12: error: cannot convert ‘const pqs::quantity<pqs::unit<-3, pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> >, double>’ to ‘int’ in initialization
  232 |    int x = q2;
      |            ^~
      |            |
      |            const pqs::quantity<pqs::unit<-3, pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> >, double>
Process terminated with status 1 (0 minute(s), 1 second(s))
1 error(s), 0 warning(s) (0 minute(s), 1 second(s))
 
*/




