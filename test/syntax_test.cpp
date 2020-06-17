

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


#if (defined(__cpp_nontype_template_args)) && (__cplusplus > 201703L)

/*
   Ideally calculations on dimensions should be expressed directly in template parameters.
   non-type template parameters allows this.
   Issues that only runtime ops and functions can be used, but maybe that works ok
*/

#define PQS_STATIC_NTTP

template <auto D, auto CF>
struct alt_unit{};

template< auto DL,auto CFL, auto DR, auto CFR>
inline constexpr auto operator * ( alt_unit<DL,CFL> const & lhs, alt_unit<DR,CFR> const & rhs)
{
   return alt_unit<DL * DR,CFL * CFR >{};
}

template <auto U, typename V = double>
struct alt_quantity{};

template< auto UL,typename VL, auto UR, typename VR>
inline constexpr auto operator * ( alt_quantity<UL,VL> const & lhs, alt_quantity<UR,VR> const & rhs)
{
   return alt_quantity<UL * UR,decltype(VL{} * VR{}) >{};
}

void nttp_test1()
{
   alt_quantity< alt_unit<exp_mass_v<1> * exp_length_v<1> , 1>{} ,double> v;
   auto constexpr x = v * v ;

  // int z = x;
}
struct  dim_velocity : decltype(exp_length_v<1> / exp_time_v<1>) {
};
void nttp_test2()
{
   alt_quantity< 
      alt_unit<dim_velocity{},2>{} ,
      double
   > v1;
   quantity< 
      si::unit<dim_velocity,unit_exp<0> >, 
      double
   > v2;
  // int constexpr x = v2  ;
}

#endif

void quantity_syntax_test() 
{
#if defined PQS_STATIC_NTTP
   nttp_test1();
   nttp_test2();
#endif
   // short syntax
   auto constexpr qa = si::length::mm<>{};  // si unit

   auto constexpr qaa = si::speed::m_per_s<>{};  // si unit

   auto constexpr qb = si::length::ft<>{};  // si unit conversion
         
   // slightly more verbose syntax
   auto qc = quantity<si::length_unit::mm, double>{};

   // construct a quantity by composing dimension
#if defined  __cpp_inline_variables
  auto qd = quantity<
      si::unit<
         decltype( exp_mass_v<1> * exp_length_v<1> / exp_time_v<2> ),
         unit_exp<-3>
      >
   >{20.0};
#else
   auto qd = quantity<
      si::unit<
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
         unit_exp<-3>
      >
   >{20.0};
#endif
   // construct a si quantity from raw ingredients
   auto qe = quantity<
      si::unit<
         base_quantity_exp_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         unit_exp<3>
      >,
      double
   >{};

   // construct a si quantity conversion from raw ingredients
   auto qf = quantity<
      si::unit_conversion<
         base_quantity_exp_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         conversion_factor<
            std::ratio<100,394>,
            unit_exp<3>
         >
      >,
      double
   >{};

  //---------------------------------------------

  // uncomment to test how quantity appears in error message
  // int x = qd;
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}