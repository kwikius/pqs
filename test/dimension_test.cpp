
#include "test.hpp"
#include <pqs/units/length_unit.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/bits/binary_op.hpp>

namespace {

   void length_dimension_test()
   {
       typedef pqs::length_unit::mm::dimension dimension;

       QUAN_CHECK((dimension::num_elements == 1))

       typedef pqs::meta::front<dimension>::type base_dimension1;

       QUAN_CHECK((std::is_same<base_dimension1,pqs::exp_length<1> >::value))
       
       typedef pqs::meta::back<dimension>::type base_dimension2;

       QUAN_CHECK((std::is_same<base_dimension2,pqs::exp_length<1> >::value)) 

       typedef pqs::meta::pop_front<dimension>::type empty_dimension;

       QUAN_CHECK((std::is_same<empty_dimension,pqs::base_quantity_exp_list<> >::value))
       QUAN_CHECK((empty_dimension::num_elements == 0))
   }

//   using pqs::exp_length;
//   using pqs::exp_mass;
//   using pqs::exp_time;
//   using pqs::exp_temperature;
//   using pqs::exp_current;
//   using pqs::exp_substance;
//   using pqs::exp_intensity;

   template <typename List>
   struct sort : pqs::meta::merge_sort<List,pqs::meta::detail::base_quantity_exp_sort_fun>{};

   void multiply_dimensions_test()
   {
      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<1>, 
          pqs::exp_time<-1>, 
          pqs::exp_mass<2> 
      > lhs_dimension;
      typedef pqs::base_quantity_exp_list< 
         pqs::exp_mass<2>,
         pqs::exp_time<1>
      > rhs_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::times,rhs_dimension>::type result;

      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<1>,  
         pqs::exp_mass<4> 
      > expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<-1>,
         pqs::exp_time<1>, 
         pqs::exp_mass<-2> 
      > inv_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::times,inv_dimension>::type empty_result;
      QUAN_CHECK((std::is_same<empty_result, pqs::base_quantity_exp_list<> >::value))

      typedef pqs::binary_op<lhs_dimension,pqs::times,empty_result>::type result1;

      QUAN_CHECK((std::is_same<sort<lhs_dimension>::type,result1>::value))

      typedef pqs::binary_op<empty_result, pqs::times,lhs_dimension>::type result2;

      QUAN_CHECK((std::is_same<sort<lhs_dimension>::type,result2>::value))
   }

   void divide_dimensions_test()
   {
      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<1>, 
         pqs::exp_time<-1>,
         pqs::exp_mass<2> ,
         pqs::exp_current<2> 
      > lhs_dimension;

      typedef pqs::base_quantity_exp_list<
         pqs::exp_mass<2>, 
         pqs::exp_time<1>,
         pqs::exp_length<3>, 
         pqs::exp_current<1> 
      > rhs_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::divides,rhs_dimension>::type result;

      typedef sort<
         pqs::base_quantity_exp_list<
            pqs::exp_length<-2>, 
            pqs::exp_time<-2>, 
            pqs::exp_current<1> 
         > 
      >::type expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::binary_op<lhs_dimension,pqs::divides,lhs_dimension>::type empty_result;

      QUAN_CHECK( (std::is_same<empty_result,pqs::base_quantity_exp_list<> >::value ))

      typedef pqs::binary_op<pqs::base_quantity_exp_list<>,pqs::divides,lhs_dimension>::type result2;

      typedef sort<
         pqs::base_quantity_exp_list<
            pqs::exp_length<-1>, 
            pqs::exp_time<1>,
            pqs::exp_mass<-2> ,
            pqs::exp_current<-2> 
         >
      >::type expected2;

      QUAN_CHECK( (std::is_same<result2,expected2>::value ))

      QUAN_CHECK( ( std::is_same<result2,pqs::unary_op<pqs::meta::reciprocal,lhs_dimension>::type>::value) )
   }

   void to_power_dimension_test1()
   {

      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<1>, 
         pqs::exp_time<-1>, 
         pqs::exp_mass<2>,
         pqs::exp_current<2> 
      > dimension;
      typedef std::ratio<2> multiplier;

      typedef pqs::binary_op<dimension,struct pqs::to_power,multiplier>::type result;

      typedef sort<
         pqs::base_quantity_exp_list<
            pqs::exp_length<2>, 
            pqs::exp_time<-2>, 
            pqs::exp_mass<4>,
            pqs::exp_current<4> 
         > 
      >::type expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      // TODO fails since its is a list of zero values
      typedef pqs::binary_op<dimension,struct pqs::to_power,std::ratio<0> >::type empty_result;
    //  int x = empty_result{};
      QUAN_CHECK( (std::is_same<empty_result,pqs::base_quantity_exp_list<> >::value ))

  }

   void to_power_dimension_test2()
   {
      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<2>, 
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4> 
      > dimension;

      typedef std::ratio<2> divisor;

      typedef pqs::binary_op<
         dimension,struct pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type 
      >::type result1;

      typedef sort<
         pqs::base_quantity_exp_list<
            pqs::exp_length<1>, 
            pqs::exp_time<-1>,
            pqs::exp_mass<2>,
            pqs::exp_current<2> 
         > 
      >::type expected_result1;

      QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

      typedef pqs::binary_op<
         result1,struct pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type
      >::type result2;

      typedef sort <
         pqs::base_quantity_exp_list<
            pqs::expr_length<1,2>,
            pqs::expr_time<-1,2>, 
            pqs::exp_mass<1>,
            pqs::exp_current<1> 
         >
      >::type expected_result2;

      QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
     
  }

  void reciprocal_dimension_test()
  {
      typedef pqs::base_quantity_exp_list<
         pqs::exp_length<2>,
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4> 
      > dimension;

      typedef pqs::unary_op<pqs::meta::reciprocal,dimension>::type result1;

      typedef sort<
         pqs::base_quantity_exp_list<
            pqs::exp_length<-2>, 
            pqs::exp_time<2>, 
            pqs::exp_mass<-4>,
            pqs::exp_current<-4> 
         > 
      >::type expected_result1;
  
     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::base_quantity_exp_list<
         pqs::expr_length<1,2>,
         pqs::expr_time<-5,2>, 
         pqs::exp_mass<1> ,
         pqs::exp_current<10> 
     > dimension2;

     typedef pqs::unary_op<pqs::meta::reciprocal,dimension2>::type result2;

     typedef sort<
         pqs::base_quantity_exp_list<
            pqs::expr_length<-1,2>,
            pqs::expr_time<5,2>,
            pqs::exp_mass<-1>,
            pqs::exp_current<-10> 
         > 
      >::type expected_result2;

     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
  }

  void compare_dimension_test()
  {
      typedef pqs::base_quantity_exp_list<
         pqs::exp_time<-2>, 
         pqs::exp_mass<4>,
         pqs::exp_current<4>, 
         pqs::exp_length<2> 
      > dimension1;

      typedef pqs::base_quantity_exp_list<
         pqs::expr_length<4,2>,
         pqs::exp_time<-2>, 
         pqs::exp_current<4>, 
         pqs::exp_mass<4>
      > dimension2;

      typedef pqs::base_quantity_exp_list<
         pqs::expr_length<-1,2>, 
         pqs::expr_time<5,2>, 
         pqs::exp_current<-10>, 
         pqs::exp_mass<-1>
      > dimension3;

      typedef pqs::binary_op<dimension1,pqs::equal_to, dimension2> are_equal12;
      QUAN_CHECK(are_equal12::value == true)
      typedef pqs::binary_op<dimension1,pqs::not_equal_to, dimension2> are_not_equal12;
      QUAN_CHECK(are_not_equal12::value == false)

      typedef pqs::binary_op<dimension1, pqs::equal_to,dimension3> are_equal13;
      QUAN_CHECK(are_equal13::value == false)
      typedef pqs::binary_op<dimension1,pqs::not_equal_to, dimension3> are_not_equal13;
      QUAN_CHECK(are_not_equal13::value == true)
  }
}

void dimension_test()
{
   length_dimension_test();
   multiply_dimensions_test();
   divide_dimensions_test();
   to_power_dimension_test1();
   to_power_dimension_test2();
   reciprocal_dimension_test();
   compare_dimension_test();
}


