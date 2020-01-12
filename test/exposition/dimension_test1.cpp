

#include <type_traits>
#include <pqs/bits/dimension.hpp>
#include <pqs/exposition/base_quantity_exp.hpp>

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>

using pqs::dimension;
using pqs_exposition::exp;
using pqs::base_length;
using pqs::base_time;
using pqs::base_mass;
using pqs::dimension;
using pqs::meta::merge_dim;

void dimension_test1()
{
   typedef dimension<> empty;
   typedef merge_dim<empty,pqs::times,empty >::type result0a;
   static_assert(std::is_same<result0a,empty>::value,"");
   typedef merge_dim<empty,pqs::divides,empty >::type result0b;
   static_assert(std::is_same<result0b,empty>::value,"");
   
   // n.b must be sorted
   typedef dimension<exp<base_time,1> > dim1;
   typedef merge_dim<dim1,pqs::times,dim1 >::type result1;
   typedef dimension<exp<base_time,2> > expected1;

   static_assert(std::is_same<result1,expected1>::value,"");
   static_assert(pqs::binary_op<result1,pqs::equal_to,expected1>::value,"");
  // int x = result1{};

   typedef merge_dim<dim1,pqs::divides,dim1 >::type result1a;
   typedef dimension<> expected1a;
   static_assert(std::is_same<result1a,expected1a>::value,"");

   typedef dimension<exp<base_length,-2>, exp<base_time,2> >  dim2;
   typedef merge_dim<dim1,pqs::times,dim2 >::type result2;
   typedef dimension<exp<base_length,-2>, exp<base_time,3> > expected2;
 //  static_assert(std::is_same<result2,expected2>::value,"");
   static_assert(pqs::binary_op<result2,pqs::equal_to,expected2>::value,"");

   typedef merge_dim<dim1,pqs::divides,dim2 >::type result2a;
   typedef dimension<exp<base_length,2>, exp<base_time,-1> > expected2a;
   static_assert(std::is_same<result2a,expected2a>::value,"");

   typedef dimension<exp<base_length,-1>, exp<base_time,1>, exp<base_mass,2> >  dim3;
   typedef merge_dim<dim2,pqs::times,dim3 >::type result3;
   typedef dimension<exp<base_length,-3>, exp<base_mass,2>, exp<base_time,3>  > expected3;
   static_assert(std::is_same<result3,expected3>::value,"");

   typedef merge_dim<dim2,pqs::divides,dim3 >::type result3a;
   typedef dimension<exp<base_length,-1>,exp<base_mass,-2>,exp<base_time,1> > expected3a;
   static_assert(std::is_same<result3a,expected3a>::value,"");

   typedef dimension<exp<base_length,1>, exp<base_time,1>, exp<base_mass,2> >  dim4;
   typedef merge_dim<dim3,pqs::times,dim4 >::type result4;
   typedef dimension<exp<base_mass,4>,exp<base_time,2> > expected4;
   static_assert(std::is_same<result4,expected4>::value,"");

   typedef merge_dim<dim3,pqs::divides,dim4 >::type result4a;
   typedef dimension<exp<base_length,-2> > expected4a;
   static_assert(std::is_same<result4a,expected4a>::value,"");


   typedef dimension<exp<base_length,-1>, exp<base_time,-1>, exp<base_mass,-2> >  dim5;
   typedef merge_dim<dim4,pqs::times,dim5 >::type result5;
   typedef dimension<> expected5;
   static_assert(std::is_same<result5,expected5>::value,"");

   typedef merge_dim<dim4,pqs::divides,dim5 >::type result5a;
   typedef dimension<exp<base_length,2>,exp<base_mass,4>,exp<base_time,2> >::type expected5a;
   static_assert(std::is_same<result5a,expected5a>::value,"");

}



