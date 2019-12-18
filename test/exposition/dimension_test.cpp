
#include "../test.hpp"
#include <pqs/exposition/units/length_unit.hpp>

namespace {

   void length_dimension_test()
   {
       typedef pqs_exposition::length_unit::mm::dimension dimension;

       QUAN_CHECK((dimension::num_elements == 1))

       typedef pqs::meta::front<dimension>::type base_dimension1;

       QUAN_CHECK((std::is_same<base_dimension1,pqs_exposition::dim_length<1> >::value))
       
       typedef pqs::meta::back<dimension>::type base_dimension2;

       QUAN_CHECK((std::is_same<base_dimension2,pqs_exposition::dim_length<1> >::value)) 

       typedef pqs::meta::pop_front<dimension>::type empty_dimension;

       QUAN_CHECK((std::is_same<empty_dimension,pqs::dimension<> >::value))
       QUAN_CHECK((empty_dimension::num_elements == 0))
   }

#if 0
   void get_base_dimension_from_length_dim_test()
   {
      typedef pqs_exposition::length_unit::mm::dimension dimension;
      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::length
      >::type length_dim;

      QUAN_CHECK((std::is_same<length_dim,pqs_exposition::dim_length<1> >::value))
   }
#endif
   void get_base_dimension_from_synth_dim_test()
   {
      typedef pqs::dimension<
         pqs_exposition::dim_length<1>,
         pqs_exposition::dim_time<-1>, 
         pqs_exposition::dim_mass<2>, 
         pqs_exposition::dim_temperature<3>,
         pqs_exposition::dim_current_ratio<1,3>
      > dimension;
/*
      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::length
      >::type length_dim;
      QUAN_CHECK((std::is_same<length_dim,pqs_exposition::dim_length<1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::time
      >::type time_dim;
      QUAN_CHECK((std::is_same<time_dim,pqs_exposition::dim_time<-1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::mass
      >::type mass_dim;
      QUAN_CHECK((std::is_same<mass_dim,pqs_exposition::dim_mass<2> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::temperature
      >::type temperature_dim;
      QUAN_CHECK((std::is_same<temperature_dim,pqs_exposition::dim_temperature<3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::current
      >::type current_dim;
      QUAN_CHECK((std::is_same<current_dim,pqs_exposition::dim_current_ratio<1,3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::substance
      >::type substance_dim;
      QUAN_CHECK((std::is_same<substance_dim,pqs_exposition::dim_substance<0> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::intensity
      >::type intensity_dim;
      QUAN_CHECK((std::is_same<intensity_dim,pqs_exposition::dim_intensity<0> >::value))
/*/
   }

   void add_base_dim_test()
   {
      typedef pqs::dimension<
         pqs_exposition::dim_length<1>,
         pqs_exposition::dim_time<-1>, 
         pqs_exposition::dim_mass<2>, 
         pqs_exposition::dim_temperature<3>,
         pqs_exposition::dim_current_ratio<1,3>
      > lhs_dimension;

      typedef pqs::dimension< pqs_exposition::dim_mass<2>, pqs_exposition::dim_time<1> > rhs_dimension;

      typedef pqs::dimension<> empty_dimension;
/*
      typedef pqs::detail::result_push_back_add_dims_base_dims<
         lhs_dimension,rhs_dimension, pqs::detail::base_dimension_id_t::mass,
         empty_dimension
      >::type result_dimension1;

      QUAN_CHECK((std::is_same<result_dimension1, pqs::dimension<pqs_exposition::dim_mass<4> > >::value))

      typedef pqs::detail::result_push_back_add_dims_base_dims<
         lhs_dimension,rhs_dimension,pqs::detail::base_dimension_id_t::time,
         result_dimension1
      >::type result_dimension2;

      // mass shouldnt have been added as result has zero extent
      // so no change
      QUAN_CHECK((std::is_same<result_dimension2, result_dimension1 >::value))

      typedef pqs::detail::result_push_back_subtract_dims_base_dims<
         lhs_dimension,rhs_dimension, 
         pqs::detail::base_dimension_id_t::time,
         result_dimension1
      >::type result_dimension3;

      QUAN_CHECK((std::is_same<result_dimension3, pqs::dimension<pqs_exposition::dim_mass<4>, pqs_exposition::dim_time<-2> > >::value))
*/
   }
}

namespace {

   void add_dimensions_test()
   {
      typedef pqs::dimension<pqs_exposition::dim_length<1>, pqs_exposition::dim_time<-1>, pqs_exposition::dim_mass<2> > lhs_dimension;
      typedef pqs::dimension< pqs_exposition::dim_mass<2>, pqs_exposition::dim_time<1> > rhs_dimension;

      typedef pqs::add_dimensions<lhs_dimension,rhs_dimension>::type result;

      typedef pqs::dimension<pqs_exposition::dim_length<1>,  pqs_exposition::dim_mass<4> > expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::dimension<pqs_exposition::dim_length<-1>, pqs_exposition::dim_time<1>, pqs_exposition::dim_mass<-2> > inv_dimension;

      typedef pqs::detail::add_dimensions<lhs_dimension,inv_dimension>::type empty_result;
      QUAN_CHECK((std::is_same<empty_result, pqs::dimension<> >::value))

   }

   void subtract_dimensions_test()
   {
      typedef pqs::dimension<pqs_exposition::dim_length<1>, pqs_exposition::dim_time<-1>, pqs_exposition::dim_mass<2> ,pqs_exposition::dim_current<2> > lhs_dimension;
      typedef pqs::dimension< pqs_exposition::dim_mass<2>, pqs_exposition::dim_time<1>, pqs_exposition::dim_length<3>, pqs_exposition::dim_current<1> > rhs_dimension;

      typedef pqs::detail::subtract_dimensions<lhs_dimension,rhs_dimension>::type result;

      typedef pqs::dimension<pqs_exposition::dim_length<-2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_current<1> > expected_result;

      QUAN_CHECK( (std::is_same<result,expected_result>::value ))

      typedef pqs::detail::subtract_dimensions<lhs_dimension,lhs_dimension>::type empty_result;

      QUAN_CHECK( (std::is_same<empty_result,pqs::dimension<> >::value ))
   }

// TODO: dimension_multiply (etc) in user space ?
// mpusz_units uses Q*Q -> multiply(q::d,Q::d) which is add on exps

  void multiply_dimension_test()
  {
     typedef pqs::dimension<pqs_exposition::dim_length<1>, pqs_exposition::dim_time<-1>, pqs_exposition::dim_mass<2> ,pqs_exposition::dim_current<2> > dimension;
     typedef std::ratio<2> multiplier;

     typedef pqs::detail::multiply_dimension<dimension,multiplier>::type result;

     typedef pqs::dimension<pqs_exposition::dim_length<2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_mass<4> ,pqs_exposition::dim_current<4> > expected_result;

     QUAN_CHECK( (std::is_same<result,expected_result>::value ))

     typedef pqs::detail::multiply_dimension<dimension,std::ratio<0> >::type empty_result;
     QUAN_CHECK( (std::is_same<empty_result,pqs::dimension<> >::value ))
  }

  void divide_dimension_test()
  {
     typedef pqs::dimension<pqs_exposition::dim_length<2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_mass<4> ,pqs_exposition::dim_current<4> > dimension;

     typedef std::ratio<2> divisor;

     typedef pqs::detail::divide_dimension<dimension,divisor>::type result1;

     typedef pqs::dimension<pqs_exposition::dim_length<1>, pqs_exposition::dim_time<-1>, pqs_exposition::dim_mass<2> ,pqs_exposition::dim_current<2> > expected_result1;

     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::detail::divide_dimension<result1,divisor>::type result2;

     typedef pqs::dimension<pqs_exposition::dim_length_ratio<1,2>, pqs_exposition::dim_time_ratio<-1,2>, pqs_exposition::dim_mass<1> ,pqs_exposition::dim_current<1> > expected_result2;

     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))
     
  }

  void negate_dimension_test()
  {
     typedef pqs::dimension<pqs_exposition::dim_length<2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_mass<4> ,pqs_exposition::dim_current<4> > dimension;

     typedef pqs::detail::negate_dimension<dimension>::type result1;

     typedef pqs::dimension<pqs_exposition::dim_length<-2>, pqs_exposition::dim_time<2>, pqs_exposition::dim_mass<-4> ,pqs_exposition::dim_current<-4> > expected_result1;
  
     QUAN_CHECK( (std::is_same<result1,expected_result1>::value ))

     typedef pqs::dimension<pqs_exposition::dim_length_ratio<1,2>, pqs_exposition::dim_time_ratio<-5,2>, pqs_exposition::dim_mass<1> ,pqs_exposition::dim_current<10> > dimension2;

     typedef pqs::detail::negate_dimension<dimension2>::type result2;

     typedef pqs::dimension<pqs_exposition::dim_length_ratio<-1,2>, pqs_exposition::dim_time_ratio<5,2>, pqs_exposition::dim_mass<-1> ,pqs_exposition::dim_current<-10> > expected_result2;

     QUAN_CHECK( (std::is_same<result2,expected_result2>::value ))

  }

  void compare_dimension_test()
  {
      typedef pqs::dimension<pqs_exposition::dim_length<2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_mass<4> ,pqs_exposition::dim_current<4> > dimension1;
      typedef pqs::dimension<pqs_exposition::dim_length_ratio<4,2>, pqs_exposition::dim_time<-2>, pqs_exposition::dim_mass<4> ,pqs_exposition::dim_current<4> > dimension2; 
      typedef pqs::dimension<pqs_exposition::dim_length_ratio<-1,2>, pqs_exposition::dim_time_ratio<5,2>, pqs_exposition::dim_mass<-1> ,pqs_exposition::dim_current<-10> > dimension3;

      typedef pqs::detail::are_equal_dimensions<dimension1, dimension2> are_equal12;
      QUAN_CHECK(are_equal12::value == true)
      typedef pqs::detail::are_not_equal_dimensions<dimension1, dimension2> are_not_equal12;
      QUAN_CHECK(are_not_equal12::value == false)

      typedef pqs::detail::are_equal_dimensions<dimension1, dimension3> are_equal13;
      QUAN_CHECK(are_equal13::value == false)
      typedef pqs::detail::are_not_equal_dimensions<dimension1, dimension3> are_not_equal13;
      QUAN_CHECK(are_not_equal13::value == true)
  }
}

void dimension_test()
{
   length_dimension_test();
   get_base_dimension_from_length_dim_test();
   get_base_dimension_from_synth_dim_test();
   add_base_dim_test();
   add_dimensions_test();
   subtract_dimensions_test();
   multiply_dimension_test();
   divide_dimension_test();
   negate_dimension_test();
   compare_dimension_test();
}

