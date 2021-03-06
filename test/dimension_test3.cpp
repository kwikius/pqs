
#include "test.hpp"
#include <type_traits>
#include <pqs/types/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/quantity.hpp>
#include <pqs/concepts/associated/dimension_to_fixed_string.hpp>
#include <pqs/systems/imperial/measurement_system.hpp>
#include <pqs/systems/si/quantity/measurement_system.hpp>

using namespace pqs;

namespace {



   void mul_ee_test()
   {
      using x = std::remove_cvref_t< decltype(abstract_length_v / abstract_time_v) >;

      static_assert(std::is_same_v<x,dimension_list<exp_length<1>,exp_time<-1> > >,"");

      using y = std::remove_cvref_t< decltype( pow<-1>(abstract_time_v) * abstract_length_v ) >;

      static_assert(std::is_same_v<y,dimension_list<exp_length<1>,exp_time<-1> > >,"");

      using z = std::remove_cvref_t<decltype( std::declval<x>() * abstract_time_v)>;
      static_assert(std::is_same_v<z,exp_length<1> >,"");
   
      using a = decltype(std::declval<x>() * pow<2>(abstract_current_v) / pow<2>(abstract_time_v) ) ;

      static_assert( std::is_same_v<a,dimension_list<exp_length<1>, exp_time<-3>, exp_current<2> > >,"");

      using b= decltype((pow<2>(abstract_current_v) / pow<2>(abstract_time_v)) * std::declval<x>() ) ;

      static_assert( std::is_same_v<a,dimension_list<exp_length<1>, exp_time<-3>, exp_current<2> > >,"");
   }

   void dimensionless_mul_test()
   {
      auto constexpr x = abstract_length_v * pow<-1>(abstract_temperature_v) *
            pow<3>(abstract_intensity_v) * pow<-2>(abstract_mass_v);

      auto constexpr y = pow<2>(abstract_mass_v) * abstract_temperature_v * 
         pow<-1>(abstract_length_v) * pow<-2>(abstract_intensity_v) / abstract_intensity_v ;

      auto constexpr r = x * y;

      static_assert( std::is_same_v<
            std::remove_cvref_t<decltype(r)>,
            pqs::dimensionless
          > ,"");
   }

   void dimensionless_divide_test()
   {
      auto constexpr x = abstract_length_v * pow<-1>(abstract_temperature_v) *
            pow<3>(abstract_intensity_v) * pow<-2>(abstract_mass_v);

      auto constexpr y = pow<-2>(abstract_mass_v) / abstract_temperature_v * 
         abstract_length_v * pow<5>(abstract_intensity_v) / pow<2>(abstract_intensity_v) ;

      auto constexpr r = x / y;

      static_assert( std::is_same_v<
            std::remove_cvref_t<decltype(r)>,
            pqs::dimensionless
          > ,"");
   }

   void dimension_list_example()
   {
      auto constexpr acc = abstract_length_v / pow<2>(abstract_time_v) ;

      static_assert( dimension<decltype(acc)>);
      static_assert( is_dimension_list<decltype(acc)>);

      auto constexpr acc_str_si = 
         dimension_to_fixed_string<
            si_measurement_system,charset_utf8
         >(acc);

      auto constexpr acc_str_fps = 
         dimension_to_fixed_string<
            imperial_measurement_system,charset_utf8
         >(acc);

     // std::cout << "acc_v1 dimension in S.I. = " << acc_str_si <<'\n';
     // std::cout << "acc_v1 dimension in f.p.s = " << acc_str_fps <<'\n';

      auto constexpr acc_v2 = abstract_length_v * pow<-2>(abstract_time_v); // alternate form

      static_assert( acc_v2 == acc );  
   }
}

void dimension_test3()
{
   mul_ee_test();
   dimensionless_mul_test();
   dimensionless_divide_test();
   dimension_list_example();

}