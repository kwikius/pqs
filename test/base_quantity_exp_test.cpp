
#include "test.hpp"

#include <pqs/types/base_quantities.hpp>

using pqs::exp_length;
using pqs::exp_time;
using pqs::exp_mass;
using pqs::binary_op;
using pqs::binary_op_t;
using pqs::times;
using pqs::divides;
using pqs::to_power;

namespace {

  /**
   * @brief Test base_quantity_exponent on exponents of all SI base_quantities
   *
   */
   void is_base_quantity_exp_test()
   {
       static_assert( not pqs::base_quantity_exponent<int> );

       static_assert( not pqs::base_quantity_exponent<pqs::base_length> );

       static_assert( pqs::base_quantity_exponent< exp_length<-1> > );
       static_assert( pqs::base_quantity_exponent< exp_length<1> > );
       static_assert( pqs::base_quantity_exponent< exp_length<2> > );
       static_assert( pqs::base_quantity_exponent< exp_length<-2,3> > );

       static_assert( pqs::base_quantity_exponent< exp_mass<-1> > );
       static_assert( pqs::base_quantity_exponent< exp_mass<1> > );
       static_assert( pqs::base_quantity_exponent< exp_mass<2> > );
       static_assert( pqs::base_quantity_exponent< exp_mass<-2,3> > );

       static_assert( pqs::base_quantity_exponent< exp_time<-1> > );
       static_assert( pqs::base_quantity_exponent< exp_time<1> > );
       static_assert( pqs::base_quantity_exponent< exp_time<2> > );
       static_assert( pqs::base_quantity_exponent< exp_time<-2,3> > );

       static_assert( pqs::base_quantity_exponent< pqs::exp_current<-1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_current<1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_current<2> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_current<-2,3> > );

       static_assert( pqs::base_quantity_exponent< pqs::exp_temperature<-1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_temperature<1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_temperature<2> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_temperature<-2,3> > );

       static_assert( pqs::base_quantity_exponent< pqs::exp_substance<-1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_substance<1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_substance<2> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_substance<-2,3> > );

       static_assert( pqs::base_quantity_exponent< pqs::exp_intensity<-1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_intensity<1> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_intensity<2> > );
       static_assert( pqs::base_quantity_exponent< pqs::exp_intensity<-2,3> > );
   }

  /**
   * @brief Check of_same_base_quantity functionality
   */
   void of_same_base_quantity_test()
   {
      
      using tl = exp_length<-2> ;
      using tr = exp_length<3> ;
      using tx = exp_length<3,2>;

      using ty = exp_time<2>;

      static_assert( pqs::of_same_base_quantity<tl,tr> );
      static_assert( pqs::of_same_base_quantity<tr,tl> );
      static_assert( pqs::of_same_base_quantity<tl,tx> );
      static_assert( not pqs::of_same_base_quantity<tl,ty> ); 
   }

   /**
    *  @brief test get_base_quantity functionality
    */
   void get_base_quantity_test()
   {
      using tl = exp_length<2> ;
      using base_type1 = pqs::get_base_quantity<tl> ;
      static_assert( pqs::base_quantity<base_type1>  );
      static_assert( std::is_same_v<base_type1,pqs::base_length> );
   }

   /**
    *  @brief add base_quantity_exponent tests
    */ 
   void add_test_int_int_int()
   {
      using tl = exp_length<2>;
      using tr = exp_length<3>;
      static_assert(pqs::impl::detail::is_std_ratio<std::ratio<5,1> >::value);
      using result_type = binary_op_t<tl,times,tr> ;
      using ratio = pqs::get_exponent<result_type>;

      static_assert(ratio::num == 5);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<5> > );
   }

   void add_test_r_int_int()
   {
      using tl = exp_length<20,10>;
      using tr = exp_length<3>;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 5);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<5> >);
   }

   void add_test_int_r_int()
   {
      using tl = exp_length<3>;
      using tr = exp_length<20,10> ;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio = pqs::get_exponent<result_type> ;
      static_assert(ratio::num == 5);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<5> >);
   }

   void add_test_r_r_int()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<10,20>;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 1);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<1> >); 
   }

   void add_test_int_r_r()
   {
      using tl = exp_length<3>;
      using tr = exp_length<1,2>;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio =  pqs::get_exponent<result_type>;
      static_assert(ratio::num == 7);
      static_assert(ratio::den == 2);
      static_assert(std::is_same_v<result_type,exp_length<7,2> >); 
   }

   void add_test_r_int_r()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<3>;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 7);
      static_assert(ratio::den == 2);
      static_assert(std::is_same_v<result_type,exp_length<7,2> >);
   }

   void add_test_r_r_r()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<1,3>;
      using result_type = binary_op_t<tl,times,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 5);
      static_assert(ratio::den == 6);
      static_assert(std::is_same_v<result_type,exp_length<5,6> >); 
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
      using tl = exp_length<2>;
      using tr = exp_length<3>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == -1);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<-1> >) ;
   }

  void subtract_test_r_int_int()
   {
      using tl = exp_length<20,10>;
      using tr = exp_length<3>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == -1);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<-1> >); 
   };

   void subtract_test_int_r_int()
   {
      using tl = exp_length<3>;
      using tr = exp_length<20,10>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 1);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<1> >); 
   }

   void subtract_test_r_r_int()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<10,20>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 0);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,pqs::dimensionless>); 
   }

   void subtract_test_int_r_r()
   {
      using tl = exp_length<3>;
      using tr = exp_length<1,2>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 5);
      static_assert(ratio::den == 2);
      static_assert(std::is_same_v<result_type,exp_length<5,2> >);
   }

   void subtract_test_r_int_r()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<3>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == -5);
      static_assert(ratio::den == 2);
      static_assert( std::is_same_v<result_type,exp_length<-5,2> > );
   }

   void subtract_test_r_r_r()
   {
      using tl = exp_length<1,2>;
      using tr = exp_length<1,3>;
      using result_type = binary_op_t<tl,divides,tr>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 1);
      static_assert(ratio::den == 6);
      static_assert(std::is_same_v<result_type,exp_length<1,6> >);
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
      using tl = exp_length<-5>;
      using result_type = pqs::unary_op_t<pqs::meta::reciprocal,tl>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 5);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_length<5> >);
   }

   void r_negate_test()
   {
      using tl = exp_length<5,7>;
      using result_type = pqs::unary_op_t<pqs::meta::reciprocal,tl>;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == -5);
      static_assert(ratio::den == 7);
      static_assert(std::is_same_v<result_type,exp_length<-5,7> > );
   }

   void negate_test()
   {
      int_negate_test();
      r_negate_test();
   }

   void multiply_test_int_int()
   {
      using tl = exp_mass<5> ;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<4,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 10);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_mass<10> >);
   }

   void multiply_test_int_r()
   {
      using tl = exp_mass<5> ;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<3,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 15);
      static_assert(ratio::den == 2);
      static_assert(std::is_same_v<result_type,exp_mass<15,2> >);
   }

   void multiply_test_r_r()
   {
      using tl = exp_mass<5,8> ;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<3,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 15);
      static_assert(ratio::den == 16);
      static_assert(std::is_same_v<result_type,exp_mass<15,16> > );
   }

   void multiply_test_r_int()
   {
      using tl = exp_mass<5,8>;
      using result_type = binary_op_t<tl,pqs::to_power, std::ratio<16,5> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 2);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_mass<2> >);
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
      using tl = exp_mass<5>;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<4,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 10);
      static_assert(ratio::den == 1);
      static_assert( std::is_same_v<result_type,exp_mass<10> > );
   }

   void divide_test_int_r()
   {
      using tl = exp_mass<5>;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<3,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 15);
      static_assert(ratio::den == 2);
      static_assert( std::is_same_v<result_type,exp_mass<15,2> >);
   }

   void divide_test_r_r()
   {
      using tl = exp_mass<5,8>;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<3,2> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == 15);
      static_assert(ratio::den == 16);
      static_assert(std::is_same_v<result_type,exp_mass<15,16> >);
   }

   void divide_test_r_int()
   {
      using tl = exp_mass<5,8>;
      using result_type = pqs::binary_op_t<tl,pqs::to_power, std::ratio<-16,5> >;
      using ratio = pqs::get_exponent<result_type>;
      static_assert(ratio::num == -2);
      static_assert(ratio::den == 1);
      static_assert(std::is_same_v<result_type,exp_mass<-2> >);
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
      using tl = exp_mass<5> ;
      using tr = exp_mass<5>;
      static_assert(pqs::binary_op_v<tl,pqs::equal_to,tr> == true);
   }

   void equal_to_int_r_test()
   {
      using tl = exp_mass<5>;
      using tr = exp_mass<15,3>;
      static_assert(pqs::binary_op_v<tl,pqs::equal_to,tr> == true);
   }

   void equal_to_r_r_test()
   {
      using tl = exp_mass<100,20>;
      using tr = exp_mass<1000,200>;
      static_assert(pqs::binary_op_v<tl,pqs::equal_to,tr> == true);
   }

   void equal_to_test()
   {
      equal_to_int_int_test();
      equal_to_int_r_test();
      equal_to_r_r_test();
   }

   void not_equal_to_int_int_test()
   {
      using tl = exp_mass<5>;
      using tr = exp_mass<4> ;
      static_assert( pqs::binary_op_v<tl,pqs::not_equal_to,tr> == true);
   }

   void not_equal_to_int_r_test()
   {
      using tl = exp_mass<5>;
      using tr = exp_mass<5,3>;
      static_assert( pqs::binary_op_v<tl,pqs::not_equal_to,tr> == true);
   }

   void not_equal_to_r_r_test()
   {
      using tl = exp_mass<100,500>;
      using tr = exp_mass<500,200>;
      static_assert( pqs::binary_op_v<tl,pqs::not_equal_to,tr> == true);
   }

   void not_equal_to_test()
   {
      not_equal_to_int_int_test();
      not_equal_to_int_r_test();
      not_equal_to_r_r_test();
   }

   void is_zero_test_int()
   {
      using zero = exp_mass<0>;
      using one = exp_mass<1> ;
      
      static_assert(pqs::base_quantity_exp_is_zero<zero>);
      static_assert(!pqs::base_quantity_exp_is_zero<one>);
   }

   void is_zero_test_r()
   {
      using zero = exp_mass<0,3> ;
      using one = exp_mass<1,1>;
      
      static_assert(pqs::base_quantity_exp_is_zero<zero>);
      static_assert(!pqs::base_quantity_exp_is_zero<one>);
   }

   void is_zero_test()
   {
      is_zero_test_int();
      is_zero_test_r();
   }

} // namespace

void base_quantity_exp_test()
{
   is_base_quantity_exp_test();
   get_base_quantity_test();
   of_same_base_quantity_test();
   add_test();
   subtract_test();
   negate_test();
   multiply_test();
   divide_test();
   equal_to_test();
   not_equal_to_test();
   is_zero_test();
}

