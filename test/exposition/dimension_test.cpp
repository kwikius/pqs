
#include "../test.hpp"
#include <pqs/exposition/units/length_unit.hpp>
#include <pqs/bits/base_quantities.hpp>

namespace {

   void length_dimension_test()
   {
       typedef pqs_exposition::length_unit::mm::dimension dimension;

       QUAN_CHECK((dimension::num_elements == 1))


       typedef pqs::meta::front<dimension>::type base_dimension1;

     //  int x= base_dimension1{};

       QUAN_CHECK((std::is_same<base_dimension1,pqs_exposition::exp<pqs::base_length,1> >::value))
       
       typedef pqs::meta::back<dimension>::type base_dimension2;

       QUAN_CHECK((std::is_same<base_dimension2,pqs_exposition::exp<pqs::base_length,1> >::value)) 

       typedef pqs::meta::pop_front<dimension>::type empty_dimension;

       QUAN_CHECK((std::is_same<empty_dimension,pqs::dimension<> >::value))
       QUAN_CHECK((empty_dimension::num_elements == 0))
   }


//   void get_base_dimension_from_length_dim_test()
//   {
//      typedef pqs_exposition::length_unit::mm::dimension dimension;
//      typedef pqs::detail::get_base_dimension<
//         dimension,pqs::detail::exp<base_dimension_id_t::length
//      >::type length_dim;
//
//      QUAN_CHECK((std::is_same<length_dim,pqs_exposition::exp<base_length,1> >::value))
//   }

   void get_base_dimension_from_synth_dim_test()
   {
      typedef pqs::dimension<
         pqs_exposition::exp<pqs::base_length,1>,
         pqs_exposition::exp<pqs::base_time,-1>, 
         pqs_exposition::exp<pqs::base_mass,2>, 
         pqs_exposition::exp<pqs::base_temperature,3>,
         pqs_exposition::exp<pqs::base_current,1,3>
      > dimension;
/*
      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::length
      >::type length_dim;
      QUAN_CHECK((std::is_same<length_dim,pqs_exposition::dim_length,1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::time
      >::type time_dim;
      QUAN_CHECK((std::is_same<time_dim,pqs_exposition::dim_time,-1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::mass
      >::type mass_dim;
      QUAN_CHECK((std::is_same<mass_dim,pqs_exposition::dim_mass,2> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::temperature
      >::type temperature_dim;
      QUAN_CHECK((std::is_same<temperature_dim,pqs_exposition::dim_temperature,3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::current
      >::type current_dim;
      QUAN_CHECK((std::is_same<current_dim,pqs_exposition::dim_current,1,3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::substance
      >::type substance_dim;
      QUAN_CHECK((std::is_same<substance_dim,pqs_exposition::dim_substance,0> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::exp<base_dimension_id_t::intensity
      >::type intensity_dim;
      QUAN_CHECK((std::is_same<intensity_dim,pqs_exposition::dim_intensity,0> >::value))
/*/
   }

   void add_base_dim_test()
   {
      typedef pqs::dimension<
         pqs_exposition::exp<pqs::base_length,1>,
         pqs_exposition::exp<pqs::base_time,-1>, 
         pqs_exposition::exp<pqs::base_mass,2>, 
         pqs_exposition::exp<pqs::base_temperature,3>,
         pqs_exposition::exp<pqs::base_current,1,3>
      > lhs_dimension;

      typedef pqs::dimension< pqs_exposition::exp<pqs::base_mass,2>, pqs_exposition::exp<pqs::base_time,1> > rhs_dimension;

      typedef pqs::dimension<> empty_dimension;

   }
}

namespace {

   using pqs::base_length;
   using pqs::base_mass;
   using pqs::base_time;
   using pqs::base_temperature;
   using pqs::base_current;
   using pqs::base_substance;
   using pqs::base_intensity;

   template <typename List>
   struct sort : pqs::meta::merge_sort<List,pqs::meta::detail::base_quantity_exp_sort_fun>{};

   void multiply_dimensions_test()
   {
      typedef pqs::dimension<
         pqs_exposition::exp<base_length,1>, 
          pqs_exposition::exp<base_time,-1>, 
          pqs_exposition::exp<base_mass,2> 
      > lhs_dimension;
      typedef pqs::dimension< 
         pqs_exposition::exp<base_mass,2>,
         pqs_exposition::exp<base_time,1>
      > rhs_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::times,rhs_dimension>::type result;

      typedef pqs::dimension<
         pqs_exposition::exp<base_length,1>,  
         pqs_exposition::exp<base_mass,4> 
      > expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::dimension<
         pqs_exposition::exp<base_length,-1>,
         pqs_exposition::exp<base_time,1>, 
         pqs_exposition::exp<base_mass,-2> 
      > inv_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::times,inv_dimension>::type empty_result;
      QUAN_CHECK((std::is_same<empty_result, pqs::dimension<> >::value))

      typedef pqs::binary_op<lhs_dimension,pqs::times,empty_result>::type result1;

      QUAN_CHECK((std::is_same<sort<lhs_dimension>::type,result1>::value))

      typedef pqs::binary_op<empty_result, pqs::times,lhs_dimension>::type result2;

      QUAN_CHECK((std::is_same<sort<lhs_dimension>::type,result2>::value))
   }

   void divide_dimensions_test()
   {
      typedef pqs::dimension<
         pqs_exposition::exp<base_length,1>, 
         pqs_exposition::exp<base_time,-1>,
         pqs_exposition::exp<base_mass,2> ,
         pqs_exposition::exp<base_current,2> 
      > lhs_dimension;

      typedef pqs::dimension<
         pqs_exposition::exp<base_mass,2>, 
         pqs_exposition::exp<base_time,1>,
         pqs_exposition::exp<base_length,3>, 
         pqs_exposition::exp<base_current,1> 
      > rhs_dimension;

      typedef pqs::binary_op<lhs_dimension,pqs::divides,rhs_dimension>::type result;

      typedef sort<
         pqs::dimension<
            pqs_exposition::exp<base_length,-2>, 
            pqs_exposition::exp<base_time,-2>, 
            pqs_exposition::exp<base_current,1> 
         > 
      >::type expected_result;


      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::binary_op<lhs_dimension,pqs::divides,lhs_dimension>::type empty_result;

      QUAN_CHECK( (std::is_same<empty_result,pqs::dimension<> >::value ))

      typedef pqs::binary_op<pqs::dimension<>,pqs::divides,lhs_dimension>::type result2;

     // int x = result2{};
      typedef sort<
         pqs::dimension<
            pqs_exposition::exp<base_length,-1>, 
            pqs_exposition::exp<base_time,1>,
            pqs_exposition::exp<base_mass,-2> ,
            pqs_exposition::exp<base_current,-2> 
         >
      >::type expected2;

      QUAN_CHECK( (std::is_same<result2,expected2>::value ))

      QUAN_CHECK( ( std::is_same<result2,pqs::unary_op<pqs::meta::reciprocal,lhs_dimension>::type>::value) )
   }

// TODO: dimension_multiply (etc) in user space ?
// mpusz_units uses Q*Q -> multiply(q::d,Q::d) which is add on exps
#if 0
  void to_power_dimension_test1()
  {
     typedef pqs::dimension<pqs_exposition::exp<base_length,1>, pqs_exposition::exp<base_time,-1>, pqs_exposition::exp<base_mass,2> ,pqs_exposition::exp<base_current,2> > dimension;
     typedef std::ratio<2> multiplier;

     typedef pqs::binary_op<dimension,pqs::to_power,multiplier>::type result;

     int x = result{};

     typedef pqs::dimension<pqs_exposition::exp<base_length,2>, pqs_exposition::exp<base_time,-2>, pqs_exposition::exp<base_mass,4> ,pqs_exposition::exp<base_current,4> > expected_result;

     QUAN_CHECK( (std::is_same<result,expected_result>::value ))

     typedef pqs::binary_op<dimension,pqs::to_power,std::ratio<0> >::type empty_result;
     QUAN_CHECK( (std::is_same<empty_result,pqs::dimension<> >::value ))
  }

  //TODO replace divide by to_powerr and switch ratio n, d
  void to_power_dimension_test2()
  {
     typedef pqs::dimension<pqs_exposition::exp<base_length,2>, pqs_exposition::exp<base_time,-2>, pqs_exposition::exp<base_mass,4> ,pqs_exposition::exp<base_current,4> > dimension;

     typedef std::ratio<2> divisor;

     typedef pqs::binary_op<dimension,pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type >::type result1;

     typedef pqs::dimension<pqs_exposition::exp<base_length,1>, pqs_exposition::exp<base_time,-1>, pqs_exposition::exp<base_mass,2> ,pqs_exposition::exp<base_current,2> > expected_result1;

     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::binary_op<result1,pqs::to_power,typename pqs::unary_op<pqs::meta::reciprocal,divisor>::type>::type result2;

     typedef pqs::dimension<pqs_exposition::exp<base_length,1,2>, pqs_exposition::exp<base_time,-1,2>, pqs_exposition::exp<base_mass,1> ,pqs_exposition::exp<base_current,1> > expected_result2;

     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
     
  }
#endif
  void reciprocal_dimension_test()
  {
      typedef pqs::dimension<
         pqs_exposition::exp<base_length,2>,
         pqs_exposition::exp<base_time,-2>, 
         pqs_exposition::exp<base_mass,4>,
         pqs_exposition::exp<base_current,4> 
      > dimension;

      typedef pqs::unary_op<pqs::meta::reciprocal,dimension>::type result1;

   //   int x = result1{};
      typedef sort<
         pqs::dimension<pqs_exposition::exp<
            base_length,-2>, 
            pqs_exposition::exp<base_time,2>, 
            pqs_exposition::exp<base_mass,-4>,
            pqs_exposition::exp<base_current,-4> 
         > 
      >::type expected_result1;
  
     //###
     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::dimension<
         pqs_exposition::exp<base_length,1,2>,
         pqs_exposition::exp<base_time,-5,2>, 
         pqs_exposition::exp<base_mass,1> ,
         pqs_exposition::exp<base_current,10> 
     > dimension2;

     typedef pqs::unary_op<pqs::meta::reciprocal,dimension2>::type result2;

     typedef sort<
         pqs::dimension<
            pqs_exposition::exp<base_length,-1,2>,
            pqs_exposition::exp<base_time,5,2>,
            pqs_exposition::exp<base_mass,-1>,
            pqs_exposition::exp<base_current,-10> 
         > 
      >::type expected_result2;

     //###
     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))

  }

  void compare_dimension_test()
  {
      typedef pqs::dimension<pqs_exposition::exp<base_length,2>, pqs_exposition::exp<base_time,-2>, pqs_exposition::exp<base_mass,4> ,pqs_exposition::exp<base_current,4> > dimension1;
      typedef pqs::dimension<pqs_exposition::exp<base_length,4,2>, pqs_exposition::exp<base_time,-2>, pqs_exposition::exp<base_mass,4> ,pqs_exposition::exp<base_current,4> > dimension2; 
      typedef pqs::dimension<pqs_exposition::exp<base_length,-1,2>, pqs_exposition::exp<base_time,5,2>, pqs_exposition::exp<base_mass,-1> ,pqs_exposition::exp<base_current,-10> > dimension3;

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
  // get_base_dimension_from_length_dim_test();
   get_base_dimension_from_synth_dim_test();
   add_base_dim_test();
   multiply_dimensions_test();
   divide_dimensions_test();
 //  to_power_dimension_test1();
  // to_power_dimension_test2();
   reciprocal_dimension_test();
   compare_dimension_test();
}


