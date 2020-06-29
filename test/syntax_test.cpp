
#include "test.hpp"

#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>
#include <iostream>

using namespace pqs;

void custom_test1()
{
  // pqs::abstract_length<1> * 
}

void custom_test2()
{
   // derivation can be used to make a custom dimension
   struct  abstract_velocity : 
      pqs::named<"abstract_velocity"> ,
      decltype( 
         abstract_length<> / abstract_time<>
      ) 
   {} ;

   basic_quantity< 
      si::unit<abstract_velocity,exponent10<0> >, 
      double
   > v2;

   static_assert(pqs::is_dimension<abstract_velocity>,"");
   std::cout << "##### " << abstract_velocity::name << " ####\n";
   static_assert(pqs::is_quantity<decltype(v2)>,"");

   static_assert(pqs::dimension<abstract_velocity>,"");
   static_assert(pqs::quantity<decltype(v2)>,"");

   static_assert(pqs::is_dimension_legacy<abstract_velocity>::value,"");
   static_assert(pqs::is_quantity_legacy<decltype(v2)>::value,"");

   using u = pqs::get_unit<decltype(v2)>;
   static_assert(std::is_same<u, si::unit<abstract_velocity,exponent10<0> > >::value,"");
   using s = pqs::get_measurement_system_legacy<u>::type;
   static_assert( std::is_same<s,pqs::si_measurement_system>::value,"");
   using cf = pqs::get_conversion_factor_legacy<u>::type;
   static_assert(std::is_same< cf, pqs::conversion_factor<std::ratio<1>,pqs::exponent10<0> > >::value,"");
   using d = pqs::get_dimension_legacy<u>::type;
   static_assert(std::is_same<d,abstract_velocity>::value,"");
   
   using v = pqs::get_numeric_type<decltype(v2)>;
   static_assert(std::is_same<v,double>::value,"");

   auto nv = get_numeric_value(v2);

   QUAN_CHECK(nv == 0.)
   
}

namespace pqs{

   template <int N>
   struct pow10_t{

      template <intmax_t N1, intmax_t D1>
      friend constexpr 
      pqs::conversion_factor<
         std::ratio<N1,D1>,
         pqs::exponent10<N> 
      > operator * ( std::ratio<N1,D1>, pow10_t )
      {
         return {};
      }

   };

   template <int N>
   inline constexpr auto pow_10 = pow10_t<N>{};

}

void quantity_syntax_test() 
{

   custom_test1();
   custom_test2();

   // short syntax
   auto constexpr qa = si::length::mm<>{};  // si unit

   auto constexpr qaa = si::speed::m_per_s<>{};  // si unit

   auto constexpr qb = si::length::ft<>{};  // si unit conversion

   using qbu = pqs::get_unit<decltype(qb)>;

   using qbcf = pqs::get_conversion_factor<qbu>;

   std::cout << "----------------" << qbu::name << "-------\n";
         
   // slightly more verbose syntax
   auto qc = basic_quantity<si::length_unit::mm, double>{};

   // construct a quantity by composing dimension
   auto qd = basic_quantity<
      si::unit<
         decltype( abstract_mass<> * abstract_length<> / abstract_time<2> ),
         exponent10<-3>
      >
   >{20.0};

   auto constexpr qx = basic_quantity<
      si::unit_conversion<
         decltype( abstract_mass<> * abstract_length<> / abstract_time<2> ),
         decltype( std::ratio<383,100>{} * pqs::pow_10<-3> )
      >
   >{20.0};

   // construct a si quantity from raw ingredients
   auto qe = basic_quantity<
      si::unit<
         dimension_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         exponent10<3>
      >,
      double
   >{1234567.};

   QUAN_CHECK(get_numeric_value(qe) == 1234567.)

   // construct a si quantity conversion from raw ingredients
   auto qf = basic_quantity<
      si::unit_conversion<
         dimension_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         conversion_factor<
            std::ratio<100,394>,
            exponent10<-6>
         >
      >,
      double
   >{};

  //---------------------------------------------
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}