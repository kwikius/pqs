

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

#define PQS_STATIC_NTTP

template <auto D, typename V = double>
struct alt_quantity{};

template< auto DL,typename VL, auto DR, typename VR>
inline constexpr auto operator * ( alt_quantity<DL,VL> const & lhs, alt_quantity<DR,VR> const & rhs)
{
   return alt_quantity<DL * DR,std::common_type_t<VL,VR> >{};
}

void nttp_test()
{

   alt_quantity< exp_mass_v<1> * exp_length_v<1> ,double> v;
   auto constexpr x = v * v ;
}

#endif

void quantity_syntax_test() 
{
#if defined PQS_STATIC_NTTP
   nttp_test();
#endif
   // short syntax
   auto constexpr qa = length::mm<>{};

   auto constexpr qaa = speed::m_per_s<>{};

   auto constexpr qb = length::ft<>{};
         
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
   //int x = qaa;
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}