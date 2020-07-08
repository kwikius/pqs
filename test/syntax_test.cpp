
#include "test.hpp"

#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>
#include <pqs/imperial/units/length_unit.hpp>

#include <iostream>

using namespace pqs;

using std::ratio;

void custom_test1()
{
   auto cf = ratio<100,2>{} * exponent10<3>{};

   typedef imperial::length_unit::mi type1;

    std::cout  << "imp miles name = " << imperial::length_unit::mi::name <<'\n';;
}

void custom_test2()
{
   // derivation can be used to make a custom dimension
   struct  abstract_velocity : 
      named<"abstract_velocity"> ,
      decltype( 
         abstract_length<> / abstract_time<>
      ) 
   {} ;

   basic_quantity< 
      si::unit<abstract_velocity,exponent10<0> >, 
      double
   > v2;

   static_assert(is_dimension<abstract_velocity>,"");
   std::cout << "##### " << abstract_velocity::name << " ####\n";
   static_assert(is_quantity<decltype(v2)>,"");

   static_assert(dimension<abstract_velocity>,"");
   static_assert(quantity<decltype(v2)>,"");

   static_assert(is_dimension_legacy<abstract_velocity>::value,"");
  // static_assert(is_quantity_legacy<decltype(v2)>::value,"");

   using u = get_unit<decltype(v2)>;
   static_assert(std::is_same<u, si::unit<abstract_velocity,exponent10<0> > >::value,"");
   using s = get_measurement_system_legacy<u>::type;
   static_assert( std::is_same<s,si_measurement_system>::value,"");
   using cf = get_conversion_factor_legacy<u>::type;
   static_assert(std::is_same< cf, conversion_factor<std::ratio<1>,exponent10<0> > >::value,"");
   using d = get_dimension_legacy<u>::type;
   static_assert(std::is_same<d,abstract_velocity>::value,"");
   
   using v = get_numeric_type<decltype(v2)>;
   static_assert(std::is_same<v,double>::value,"");

   auto nv = get_numeric_value(v2);

   QUAN_CHECK(nv == 0.)
   
}

void quantity_syntax_test() 
{

   custom_test1();
   custom_test2();

   // short syntax
   auto constexpr qa = si::length::mm<>{};  // si unit

   auto constexpr qaa = si::speed::m_per_s<>{};  // si unit

   auto constexpr qb = si::length::ft<>{};  // si unit conversion

   using qbu = get_unit<decltype(qb)>;

   std::cout << "----------------" << qbu::name << "-------\n";

   using qbcf = get_conversion_factor<qbu>;

   using qbe = get_exponent<qbcf>;

   QUAN_CHECK (( std::is_same_v<qbe,exponent10<-1> > ))
         
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
         decltype( std::ratio<383,100>{} * exponent10<-3>{} )
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