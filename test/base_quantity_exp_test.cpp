
#include "test.hpp"

#include <pqs/bits/base_quantities.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>

using pqs::exp_length;
using pqs::expr_length;
using pqs::exp_time;
using pqs::expr_time;
using pqs::exp_mass;
using pqs::expr_mass;

using pqs::binary_op;

using pqs::times;
using pqs::divides;
using pqs::to_power;

namespace {

   void same_id_test()
   {
      QUAN_CHECK((not pqs::is_base_quantity_exp<int>::value))

      typedef exp_length<2> tl;
      typedef exp_length<3> tr;

      QUAN_CHECK((pqs::is_base_quantity_exp<tl>::value))
      QUAN_CHECK((pqs::is_base_quantity_exp<tr>::value))
      QUAN_CHECK((pqs::of_same_base_quantity<tl,tr>::value))
      QUAN_CHECK((pqs::of_same_base_quantity<tr,tl>::value))

      typedef pqs::get_base_quantity<tl>::type base_type1;
      QUAN_CHECK((pqs::is_base_quantity<base_type1>::value))
      QUAN_CHECK((std::is_same<base_type1,pqs::base_length>::value))

      typedef expr_length<3,2> tx;
      QUAN_CHECK((pqs::is_base_quantity_exp<tx>::value))
      QUAN_CHECK((pqs::of_same_base_quantity<tl,tx>::value))

      typedef exp_time<2> ty;
      QUAN_CHECK(( not pqs::of_same_base_quantity<tl,ty>::value)) 
   }

   void add_test_int_int_int()
   {
      typedef exp_length<2> tl;
      typedef exp_length<3> tr;

      static_assert(pqs::impl::detail::is_std_ratio<std::ratio<5,1> >::value,"odd");
 
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;

      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<5> >::value) )
   }

   void add_test_r_int_int()
   {
      typedef expr_length<20,10> tl;
      typedef exp_length<3> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<5> >::value) )
   }

   void add_test_int_r_int()
   {
      typedef exp_length<3> tl;
      typedef expr_length<20,10> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<5> >::value) )
   }

   void add_test_r_r_int()
   {
      typedef expr_length<1,2> tl;
      typedef expr_length<10,20> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<1> >::value) )

   }

   void add_test_int_r_r()
   {
      typedef exp_length<3> tl;
      typedef expr_length<1,2> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 7)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_length<7,2> >::value) )
   }

   void add_test_r_int_r()
   {
      typedef expr_length<1,2> tl;
      typedef exp_length<3> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 7)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_length<7,2> >::value) )
   }

   void add_test_r_r_r()
   {
      typedef expr_length<1,2> tl;
      typedef expr_length<1,3> tr;
      typedef binary_op<tl,times,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 6)
      QUAN_CHECK( (std::is_same<result_type,expr_length<5,6> >::value) )
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
      typedef exp_length<2> tl;
      typedef exp_length<3> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == -1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<-1> >::value) )
   }

  void subtract_test_r_int_int()
   {
      typedef expr_length<20,10> tl;
      typedef exp_length<3> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == -1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<-1> >::value) )
   }

   void subtract_test_int_r_int()
   {
      typedef exp_length<3> tl;
      typedef expr_length<20,10> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<1> >::value) )
   }

   void subtract_test_r_r_int()
   {
      typedef expr_length<1,2> tl;
      typedef expr_length<10,20> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 0)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_length<0> >::value) )
   }

   void subtract_test_int_r_r()
   {
      typedef exp_length<3> tl;
      typedef expr_length<1,2> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 5)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_length<5,2> >::value) )
   }

   void subtract_test_r_int_r()
   {
      typedef expr_length<1,2> tl;
      typedef exp_length<3> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == -5)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_length<-5,2> >::value) )
   }

   void subtract_test_r_r_r()
   {
      typedef expr_length<1,2> tl;
      typedef expr_length<1,3> tr;
      typedef binary_op<tl,divides,tr>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 1)
      QUAN_CHECK(ratio::den == 6)
      QUAN_CHECK( (std::is_same<result_type,expr_length<1,6> >::value) )
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
      typedef exp_length<-5> tl;
      typedef pqs::unary_op<pqs::meta::reciprocal,tl>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      // int x = ratio{};
       QUAN_CHECK(ratio::num == 5)
       QUAN_CHECK(ratio::den == 1)
       QUAN_CHECK( (std::is_same<result_type,exp_length<5> >::value) )
   }

   void r_negate_test()
   {
      typedef expr_length<5,7> tl;
      typedef pqs::unary_op<pqs::meta::reciprocal,tl>::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == -5)
      QUAN_CHECK(ratio::den == 7)
      QUAN_CHECK( (std::is_same<result_type,expr_length<-5,7> >::value) )
   }

   void negate_test()
   {
       int_negate_test();
       r_negate_test();
   }

   void multiply_test_int_int()
   {
      typedef exp_mass<5> tl;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<4,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 10)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_mass<10> >::value) )
   }

   void multiply_test_int_r()
   {
      typedef exp_mass<5> tl;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<3,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_mass<15,2> >::value) )
   }

   void multiply_test_r_r()
   {
      typedef expr_mass<5,8> tl;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<3,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 16)
      QUAN_CHECK( (std::is_same<result_type,expr_mass<15,16> >::value) )
   }

   void multiply_test_r_int()
   {
      typedef expr_mass<5,8> tl;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<16,5> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 2)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_mass<2> >::value) )
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
      typedef exp_mass<5> tl;
     // typedef pqs::binary_op<tl,pqs::divides, std::ratio<2,4> >::type result_type;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<4,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 10)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_mass<10> >::value) )
   }

   void divide_test_int_r()
   {
      typedef exp_mass<5> tl;
      //typedef pqs::binary_op<tl,pqs::divides, std::ratio<2,3> >::type result_type;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<3,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 2)
      QUAN_CHECK( (std::is_same<result_type,expr_mass<15,2> >::value) )
   }

   void divide_test_r_r()
   {
      typedef expr_mass<5,8> tl;
    //  typedef pqs::binary_op<tl,pqs::divides, std::ratio<2,3> >::type result_type;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<3,2> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == 15)
      QUAN_CHECK(ratio::den == 16)
      QUAN_CHECK( (std::is_same<result_type,expr_mass<15,16> >::value) )
   }

   void divide_test_r_int()
   {
      typedef expr_mass<5,8> tl;
     // typedef pqs::binary_op<tl,pqs::divides, std::ratio<-5,16> >::type result_type;
      typedef pqs::binary_op<tl,pqs::to_power, std::ratio<-16,5> >::type result_type;
      typedef pqs::get_exponent<result_type>::type ratio;
      QUAN_CHECK(ratio::num == -2)
      QUAN_CHECK(ratio::den == 1)
      QUAN_CHECK( (std::is_same<result_type,exp_mass<-2> >::value) )
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
      typedef exp_mass<5> tl;
      typedef exp_mass<5> tr;
      typedef pqs::binary_op<tl,pqs::equal_to,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

  void equal_to_int_r_test()
  {
      typedef exp_mass<5> tl;
      typedef expr_mass<15,3> tr;
      typedef pqs::binary_op<tl,pqs::equal_to,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

   void equal_to_r_r_test()
  {
      typedef expr_mass<100,20> tl;
      typedef expr_mass<1000,200> tr;
      typedef pqs::binary_op<tl,pqs::equal_to,tr>::type result_type;
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
      typedef exp_mass<5> tl;
      typedef exp_mass<4> tr;
      typedef pqs::binary_op<tl,pqs::not_equal_to,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

  void not_equal_to_int_r_test()
  {
      typedef exp_mass<5> tl;
      typedef expr_mass<5,3> tr;
      typedef pqs::binary_op<tl,pqs::not_equal_to,tr>::type result_type;
      QUAN_CHECK(result_type::value == true);
  }

   void not_equal_to_r_r_test()
  {
      typedef expr_mass<100,500> tl;
      typedef expr_mass<500,200> tr;
      typedef pqs::binary_op<tl,pqs::not_equal_to,tr>::type result_type;
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
      typedef exp_mass<0> zero;
      typedef exp_mass<1> one;
      
      QUAN_CHECK(pqs::base_quantity_exp_is_zero<zero>::value)
      QUAN_CHECK(!pqs::base_quantity_exp_is_zero<one>::value)
   }

   void is_zero_test_r()
   {
      typedef expr_mass<0,3> zero;
      typedef expr_mass<1,1> one;
      
      QUAN_CHECK(pqs::base_quantity_exp_is_zero<zero>::value)
      QUAN_CHECK(!pqs::base_quantity_exp_is_zero<one>::value)
   }

   void is_zero_test()
   {
      is_zero_test_int();
      is_zero_test_r();
   }

} // namespace

void base_quantity_exp_test()
{
   same_id_test();
   add_test();
   subtract_test();
   negate_test();
   multiply_test();
   divide_test();
   equal_to_test();
   not_equal_to_test();
   is_zero_test();

}

