
#include <quan_matters/test/test.hpp>

#include <pqs/si/length_unit.hpp>
#include <quan/meta/find_if.hpp>

namespace {

   void length_dimension_test()
   {
       typedef pqs::si::length_unit::mm::dimension dimension;
       QUAN_CHECK((quan::is_model_of<quan::meta::TypeSequence_,dimension>::value))

       QUAN_CHECK((quan::meta::get_num_elements<dimension>::value == 1))

       typedef quan::meta::front<dimension>::type base_dimension1;

       QUAN_CHECK((std::is_same<base_dimension1,pqs::si::dim_length<> >::value))
       
       typedef quan::meta::back<dimension>::type base_dimension2;

       QUAN_CHECK((std::is_same<base_dimension2,pqs::si::dim_length<> >::value)) 

       typedef quan::meta::pop_front<dimension>::type empty_dimension;

       QUAN_CHECK((std::is_same<empty_dimension,pqs::dimension<> >::value))
       QUAN_CHECK((quan::meta::get_num_elements<empty_dimension>::value == 0))
   }
} // namespace

namespace pqs{ namespace si {namespace detail{

   
    template <typename D, base_dimension_id_t Id, int Size>
    struct get_base_dimension_i;

    template <typename D, base_dimension_id_t Id>
    struct get_base_dimension_i<D,Id,0> : make_base_dimension_ratio<Id, std::ratio<0,1> >{};

    template <typename D, base_dimension_id_t Id, int Size>
    struct get_base_dimension_i {

      typedef typename quan::meta::front<D>::type base_dim;
      typedef typename quan::meta::eval_if_c<
         (base_dim::base_dimension_id == Id),
         make_base_dimension_ratio<Id,typename base_dim::ratio>, // reduce
         get_base_dimension_i<typename quan::meta::pop_front<D>::type,Id,Size -1>
      >::type type;   
    };
    
    template <typename D, base_dimension_id_t Id>
    struct get_base_dimension : get_base_dimension_i<
         typename D::type, Id,quan::meta::get_num_elements<typename D::type>::value
    >{};

}}}

namespace {
   void get_base_dimension_from_length_dim_test()
   {
      typedef pqs::si::length_unit::mm::dimension dimension;
      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::length
      >::type length_dim;

      QUAN_CHECK((std::is_same<length_dim,pqs::si::dim_length<> >::value))
   }

   void get_base_dimension_from_synth_dim_test()
   {
      typedef pqs::dimension<
         pqs::si::dim_length<1>,
         pqs::si::dim_time<-1>, 
         pqs::si::dim_mass<2>, 
         pqs::si::dim_temperature<3>,
         pqs::si::dim_current_ratio<1,3>
      > dimension;

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::length
      >::type length_dim;
      QUAN_CHECK((std::is_same<length_dim,pqs::si::dim_length<1> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::time
      >::type time_dim;
      QUAN_CHECK((std::is_same<time_dim,pqs::si::dim_time<-1> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::mass
      >::type mass_dim;
      QUAN_CHECK((std::is_same<mass_dim,pqs::si::dim_mass<2> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::temperature
      >::type temperature_dim;
      QUAN_CHECK((std::is_same<temperature_dim,pqs::si::dim_temperature<3> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::current
      >::type current_dim;
      QUAN_CHECK((std::is_same<current_dim,pqs::si::dim_current_ratio<1,3> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::substance
      >::type substance_dim;
      QUAN_CHECK((std::is_same<substance_dim,pqs::si::dim_substance<0> >::value))

      typedef pqs::si::detail::get_base_dimension<
         dimension,pqs::si::detail::base_dimension_id_t::intensity
      >::type intensity_dim;
      QUAN_CHECK((std::is_same<intensity_dim,pqs::si::dim_intensity<0> >::value))
      
   }
}

void dimension_test()
{
   length_dimension_test();
   get_base_dimension_from_length_dim_test();
   get_base_dimension_from_synth_dim_test();
}


