
#include "test.hpp"

#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>
#include <iostream>

#if ! defined  __cpp_inline_variables
namespace pqs{

   constexpr pqs::exp_mass<1> mass_v;

   constexpr pqs::exp_length<1> length_v;

   constexpr pqs::exp_time<1> time_v;  

}
#endif

using namespace pqs;

void custom_test1()
{
  // pqs::da_length<1> * 
}
// derivation can be used to make a custom dimension
void custom_test2()
{
   struct  da_velocity 
#if defined  __cpp_inline_variables
   : decltype(da_length<> / da_time<>) {};
#else
   : decltype(length_v / time_v) {};
#endif


#if 0
   basic_quantity< 
      si::unit<da_velocity,pqs::exponent10<0> >, 
      double
   > v2;
#else
     basic_quantity< 
      si::unit<da_velocity,unit_exp<0> >, 
      double
   > v2;
#endif

#if defined  __cpp_inline_variables
   static_assert(pqs::is_quantity<decltype(v2)>,"");
#else
   static_assert(pqs::is_quantity_legacy<decltype(v2)>::value,"");
#endif

   using d = pqs::get_unit<decltype(v2)>;
   static_assert(std::is_same<d, si::unit<da_velocity,unit_exp<0> > >::value,"");
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
         pqs::unit_exp<N> 
      > operator * ( std::ratio<N1,D1>, pow10_t )
      {
         return {};
      }

   };
#if defined  __cpp_inline_variables
   template <int N>
   inline constexpr auto pow_10 = pow10_t<N>{};
#endif
}

void quantity_syntax_test() 
{

   custom_test1();
   custom_test2();

   // short syntax
   auto constexpr qa = si::length::mm<>{};  // si unit

   auto constexpr qaa = si::speed::m_per_s<>{};  // si unit

   auto constexpr qb = si::length::ft<>{};  // si unit conversion
         
   // slightly more verbose syntax
   auto qc = basic_quantity<si::length_unit::mm, double>{};

   // construct a quantity by composing dimension
   auto qd = basic_quantity<
      si::unit<
#if defined  __cpp_inline_variables
         decltype( da_mass<> * da_length<> / da_time<2> ),
#else
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
#endif
         unit_exp<-3>
      >
   >{20.0};

#if defined __cpp_inline_variables

   auto constexpr qx = basic_quantity<
      si::unit_conversion<
         decltype( da_mass<> * da_length<> / da_time<2> ),
         decltype( std::ratio<383,100>{} * pqs::pow_10<-3> )
      >
   >{20.0};

#else

   auto constexpr qx = basic_quantity<
      si::unit_conversion<
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
         decltype( std::ratio<383,100>{} * pqs::pow10_t<-3>{} )
      >
   >{20.0};

#endif
  // uncomment to test how quantity appears in error message
  // int xx = qx;

   // construct a si quantity from raw ingredients
   auto qe = basic_quantity<
      si::unit<
         dimension_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         unit_exp<3>
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
            unit_exp<-6>
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