
#include <quan_matters/test/test.hpp>

#include <pqs/units/length_unit.hpp>


namespace {

   void length_dimension_test()
   {
       typedef pqs::length_unit::mm::dimension dimension;
       QUAN_CHECK((quan::is_model_of<quan::meta::TypeSequence_,dimension>::value))

       QUAN_CHECK((quan::meta::get_num_elements<dimension>::value == 1))

       typedef quan::meta::front<dimension>::type base_dimension1;

       QUAN_CHECK((std::is_same<base_dimension1,pqs::dim_length<> >::value))
       
       typedef quan::meta::back<dimension>::type base_dimension2;

       QUAN_CHECK((std::is_same<base_dimension2,pqs::dim_length<> >::value)) 

       typedef quan::meta::pop_front<dimension>::type empty_dimension;

       QUAN_CHECK((std::is_same<empty_dimension,pqs::dimension<> >::value))
       QUAN_CHECK((quan::meta::get_num_elements<empty_dimension>::value == 0))
   }
} // namespace

namespace {
   void get_base_dimension_from_length_dim_test()
   {
      typedef pqs::length_unit::mm::dimension dimension;
      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::length
      >::type length_dim;

      QUAN_CHECK((std::is_same<length_dim,pqs::dim_length<> >::value))
   }

   void get_base_dimension_from_synth_dim_test()
   {
      typedef pqs::dimension<
         pqs::dim_length<1>,
         pqs::dim_time<-1>, 
         pqs::dim_mass<2>, 
         pqs::dim_temperature<3>,
         pqs::dim_current_ratio<1,3>
      > dimension;

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::length
      >::type length_dim;
      QUAN_CHECK((std::is_same<length_dim,pqs::dim_length<1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::time
      >::type time_dim;
      QUAN_CHECK((std::is_same<time_dim,pqs::dim_time<-1> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::mass
      >::type mass_dim;
      QUAN_CHECK((std::is_same<mass_dim,pqs::dim_mass<2> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::temperature
      >::type temperature_dim;
      QUAN_CHECK((std::is_same<temperature_dim,pqs::dim_temperature<3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::current
      >::type current_dim;
      QUAN_CHECK((std::is_same<current_dim,pqs::dim_current_ratio<1,3> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::substance
      >::type substance_dim;
      QUAN_CHECK((std::is_same<substance_dim,pqs::dim_substance<0> >::value))

      typedef pqs::detail::get_base_dimension<
         dimension,pqs::detail::base_dimension_id_t::intensity
      >::type intensity_dim;
      QUAN_CHECK((std::is_same<intensity_dim,pqs::dim_intensity<0> >::value))
   }
}

namespace pqs{ namespace detail{

/*
   find the base dimensions with id in lhs and rhs 
   apply Op and if result not zero add to result dimension
*/
   template <
      typename LhsD,    
      typename RhsD, 
      typename ResultD,
      pqs::detail::base_dimension_id_t Id,
      template <typename, typename> class Op
   >struct bin_op_base_dim_to_dimension_result{

       typedef Op< typename get_base_dimension<LhsD,Id>::type,
           typename get_base_dimension<RhsD,Id>::type
       >::type result_base_dim;

       typedef typename quan::meta::eval_if_c<
          base_dimension_is_zero<result_base_dim>::value,
          ResultD,
          quan::meta::push_back<ResultD,result_base_dim>
       >::type type;
   };

      template <
         typename LhsD,    
         typename RhsD, 
         typename ResultD,
         pqs::detail::base_dimension_id_t Id
      >
      struct add_base_dim_to_dimension_result :
      bin_op_base_dim_to_dimension_result<
         LhsD,
         RhsD,
         ResultD,
         Id,
         pqs::detail::add_base_dimension_ratio
      >{};

      template <
         typename LhsD,    
         typename RhsD, 
         typename ResultD,
         pqs::detail::base_dimension_id_t Id
      >
      struct subtract_base_dim_to_dimension_result :
      bin_op_base_dim_to_dimension_result<
         LhsD,
         RhsD,
         ResultD,
         Id,
         pqs::detail::subtract_base_dimension_ratio
      >{};
       

}} // pqs::detail

namespace{

   void add_base_dim_test()
   {
       typedef pqs::dimension<
         pqs::dim_length<1>,
         pqs::dim_time<-1>, 
         pqs::dim_mass<2>, 
         pqs::dim_temperature<3>,
         pqs::dim_current_ratio<1,3>
      > lhs_dimension;

       typedef pqs::dimension< pqs::dim_mass<2>, pqs::dim_time<1> > rhs_dimension;

       typedef pqs::dimension<> result_dimension;
       typedef pqs::detail::bin_op_base_dim_to_dimension_result<
         lhs_dimension,rhs_dimension,result_dimension, 
            pqs::detail::base_dimension_id_t::mass,
            pqs::detail::add_base_dimension_ratio
       >::type result_dimension1;

       QUAN_CHECK((std::is_same<result_dimension1, pqs::dimension<pqs::dim_mass<4> > >::value))


       typedef pqs::detail::add_base_dim_to_dimension_result<
         lhs_dimension,rhs_dimension,result_dimension1, 
            pqs::detail::base_dimension_id_t::time
       >::type result_dimension2;

       // mass shouldnt be added as result zero

       QUAN_CHECK((std::is_same<result_dimension2, result_dimension1 >::value))

   }
}

void dimension_test()
{
   length_dimension_test();
   get_base_dimension_from_length_dim_test();
   get_base_dimension_from_synth_dim_test();
   add_base_dim_test();
}


