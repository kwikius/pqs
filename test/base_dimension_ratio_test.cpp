
#include <quan_matters/test/test.hpp>

#include <pqs/bits/base_dimension.hpp>

using namespace pqs;

namespace {

   void add_test_int_int_int()
   {
      typedef dim_length<2> tl;
      typedef dim_length<3> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<5> >::value) )
   }

   void add_test_r_int_int()
   {
      typedef dim_length_ratio<20,10> tl;
      typedef dim_length<3> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<5> >::value) )
   }

   void add_test_int_r_int()
   {
      typedef dim_length<3> tl;
      typedef dim_length_ratio<20,10> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<5> >::value) )
   }

   void add_test_r_r_int()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length_ratio<10,20> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<1> >::value) )
      // check default arg
       QUAN_CHECK((std::is_same<result_type,dim_length<> >::value))
   }

   void add_test_int_r_r()
   {
      typedef dim_length<3> tl;
      typedef dim_length_ratio<1,2> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 7)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<7,2> >::value) )
   }

   void add_test_r_int_r()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length<3> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 7)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<7,2> >::value) )
   }

   void add_test_r_r_r()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length_ratio<1,3> tr;
      typedef detail::add_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 6)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<5,6> >::value) )
   }

   void add_test()
   {
      add_test_int_int_int();
      add_test_r_int_int();
      add_test_r_r_int();
      add_test_int_r_int();
      add_test_int_r_r();
      add_test_r_int_r();
      add_test_r_r_r();
   }

   void subtract_test_int_int_int()
   {
      typedef dim_length<2> tl;
      typedef dim_length<3> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == -1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<-1> >::value) )
   }

  void subtract_test_r_int_int()
   {
      typedef dim_length_ratio<20,10> tl;
      typedef dim_length<3> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == -1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<-1> >::value) )
   }

   void subtract_test_int_r_int()
   {
      typedef dim_length<3> tl;
      typedef dim_length_ratio<20,10> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<1> >::value) )
   }

   void subtract_test_r_r_int()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length_ratio<10,20> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 0)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_length<0> >::value) )
   }

   void subtract_test_int_r_r()
   {
      typedef dim_length<3> tl;
      typedef dim_length_ratio<1,2> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<5,2> >::value) )
   }

   void subtract_test_r_int_r()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length<3> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == -5)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<-5,2> >::value) )
   }

   void subtract_test_r_r_r()
   {
      typedef dim_length_ratio<1,2> tl;
      typedef dim_length_ratio<1,3> tr;
      typedef detail::subtract_base_dimension_ratio<tl,tr>::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 6)
      QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<1,6> >::value) )
   }

   void subtract_test()
   {
      subtract_test_int_int_int();
      subtract_test_r_int_int();
      subtract_test_r_r_int();
      subtract_test_int_r_int();
      subtract_test_int_r_r();
      subtract_test_r_int_r();
      subtract_test_r_r_r();
   }

   void int_negate_test()
   {
       typedef dim_length<-5> tl;
       typedef detail::negate_base_dimension_ratio<tl>::type result_type;
       typedef result_type::ratio ratio;
       QUAN_CHECK(ratio::num == 5)
       QUAN_CHECK(ratio::den == 1)
       QUAN_CHECK( (std::is_same<result_type,dim_length<5> >::value) )
   }

   void r_negate_test()
   {
       typedef dim_length_ratio<5,7> tl;
       typedef detail::negate_base_dimension_ratio<tl>::type result_type;
       typedef result_type::ratio ratio;
       QUAN_CHECK(ratio::num == -5)
       QUAN_CHECK(ratio::den == 7)
       QUAN_CHECK( (std::is_same<result_type,dim_length_ratio<-5,7> >::value) )
   }

   void negate_test()
   {
       int_negate_test();
       r_negate_test();
   }

   void multiply_test_int_int()
   {
      typedef dim_mass<5> tl;
      typedef detail::multiply_base_dimension_ratio<tl, std::ratio<4,2> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 10)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_mass<10> >::value) )
   }

   void multiply_test_int_r()
   {
      typedef dim_mass<5> tl;
      typedef detail::multiply_base_dimension_ratio<tl, std::ratio<3,2> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_mass_ratio<15,2> >::value) )
   }

   void multiply_test_r_r()
   {
      typedef dim_mass_ratio<5,8> tl;
      typedef detail::multiply_base_dimension_ratio<tl, std::ratio<3,2> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 16)
      QUAN_CHECK( (std::is_same<result_type,dim_mass_ratio<15,16> >::value) )
   }

   void multiply_test_r_int()
   {
      typedef dim_mass_ratio<5,8> tl;
      typedef detail::multiply_base_dimension_ratio<tl, std::ratio<16,5> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 2)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_mass<2> >::value) )
   }

   void multiply_test()
   {
       multiply_test_int_int();
       multiply_test_int_r();
       multiply_test_r_int();
       multiply_test_r_r();
   }

   void divide_test_int_int()
   {
      typedef dim_mass<5> tl;
      typedef detail::divide_base_dimension_ratio<tl, std::ratio<2,4> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 10)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_mass<10> >::value) )
   }

   void divide_test_int_r()
   {
      typedef dim_mass<5> tl;
      typedef detail::divide_base_dimension_ratio<tl, std::ratio<2,3> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,dim_mass_ratio<15,2> >::value) )
   }

   void divide_test_r_r()
   {
      typedef dim_mass_ratio<5,8> tl;
      typedef detail::divide_base_dimension_ratio<tl, std::ratio<2,3> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 16)
      QUAN_CHECK( (std::is_same<result_type,dim_mass_ratio<15,16> >::value) )
   }

   void divide_test_r_int()
   {
      typedef dim_mass_ratio<5,8> tl;
      typedef detail::divide_base_dimension_ratio<tl, std::ratio<-5,16> >::type result_type;
      typedef result_type::ratio ratio;
      QUAN_CHECK(ratio::num == -2)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,dim_mass<-2> >::value) )
   }

   void divide_test()
   {
      divide_test_int_int();
      divide_test_int_r();
      divide_test_r_int();
      divide_test_r_r();
   }

  void equal_to_int_int_test()
  {
      typedef dim_mass<5> tl;
      typedef dim_mass<5> tr;
      typedef detail::base_dimension_ratio_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

  void equal_to_int_r_test()
  {
      typedef dim_mass<5> tl;
      typedef dim_mass_ratio<15,3> tr;
      typedef detail::base_dimension_ratio_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

   void equal_to_r_r_test()
  {
      typedef dim_mass_ratio<100,20> tl;
      typedef dim_mass_ratio<1000,200> tr;
      typedef detail::base_dimension_ratio_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

   void equal_to_test()
   {
      equal_to_int_int_test();
      equal_to_int_r_test();
      equal_to_r_r_test();
   }


  void not_equal_to_int_int_test()
  {
      typedef dim_mass<5> tl;
      typedef dim_mass<4> tr;
      typedef detail::base_dimension_ratio_not_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

  void not_equal_to_int_r_test()
  {
      typedef dim_mass<5> tl;
      typedef dim_mass_ratio<5,3> tr;
      typedef detail::base_dimension_ratio_not_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

   void not_equal_to_r_r_test()
  {
      typedef dim_mass_ratio<100,500> tl;
      typedef dim_mass_ratio<500,200> tr;
      typedef detail::base_dimension_ratio_not_equal_to<tl,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }


   void not_equal_to_test()
   {
      not_equal_to_int_int_test();
      not_equal_to_int_r_test();
      not_equal_to_r_r_test();
   }

   void is_zero_test_int()
   {
         typedef dim_mass<0> zero;
         typedef dim_mass<1> one;
         
         QUAN_CHECK(detail::base_dimension_is_zero<zero>::value)
         QUAN_CHECK(!detail::base_dimension_is_zero<one>::value)
   }

   void is_zero_test_r()
   {
         typedef dim_mass_ratio<0,3> zero;
         typedef dim_mass_ratio<1,1> one;
         
         QUAN_CHECK(detail::base_dimension_is_zero<zero>::value)
         QUAN_CHECK(!detail::base_dimension_is_zero<one>::value)
   }

   void is_zero_test()
   {
      is_zero_test_int();
      is_zero_test_r();
   }

}

void base_dimension_ratio_test()
{
   add_test();
   subtract_test();
   negate_test();
   multiply_test();
   divide_test();
   equal_to_test();
   not_equal_to_test();
   is_zero_test();

}