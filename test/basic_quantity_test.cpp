#include "test.hpp"

// test interaction with time.h
#include <time.h>
#include <pqs/si/length.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/imperial/time.hpp>

#include <iostream>

struct dummy_system{ 

   typedef dummy_system type; 
};

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<::dummy_system> : std::true_type{};
   }
}

namespace {

   void basic_quantity_test1()
   {
      static_assert(pqs::is_defined<double>,"");
      pqs::basic_quantity<
         pqs::basic_unit<
            dummy_system,
            decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
            decltype( std::ratio<30,2>{} * pqs::exponent10<3>{})
         >, double
      > constexpr q{20.0};

      using tu = pqs::get_unit<decltype(q)>;

      QUAN_CHECK(( ! pqs::si::is_proper_si_unit<tu> ))
         
      using td = pqs::get_dimension<decltype(q)>;

      using tv = pqs::get_numeric_type<decltype(q)>;

      using tcf = pqs::get_conversion_factor<decltype(q)>;

      using ts = pqs::get_measurement_system<decltype(q)>;

      auto constexpr v = get_numeric_value(q);
     
      std::cout << " qs numeric value = " << v << '\n';

      QUAN_CHECK(( v == 20.0 ))

      auto constexpr r = q + q;

      QUAN_CHECK(( get_numeric_value(r) == 40.0))

   }

   void basic_quantity_test2()
   {
      auto q_si1 = pqs::si::length::m<>{1};

      QUAN_CHECK(( pqs::si::is_proper_si_unit<pqs::get_unit<decltype(q_si1)> > ))
      auto q_si2 = pqs::si::length::mm<>{321};
      QUAN_CHECK(( pqs::si::is_proper_si_unit<pqs::get_unit<decltype(q_si1)> > ))
      auto q_sir = q_si1 + q_si2;
      QUAN_CHECK( (get_numeric_value(q_sir) == 1321))
      std::cout << " q_sir numeric value = " << get_numeric_value(q_sir) << '\n';

      auto q_si3 = pqs::si::length::ft<>{6};
      auto q_sir1 = q_si1 + q_si3;
      std::cout << " q_sir1 numeric value = " << get_numeric_value(q_sir1) << '\n';

      using cf1 = pqs::get_conversion_factor<decltype(q_sir1)>;

      QUAN_CHECK(( std::is_same_v< 
         cf1, pqs::conversion_factor<std::ratio<1>,pqs::exponent10<-1> >
      > ))

      auto b = pqs::imperial::length::ft<>{1};
      auto c = pqs::imperial::length::yd<>{2};
      auto d = b + c;
      QUAN_CHECK( (get_numeric_value(d) == 7))
      std::cout << " imp numeric value = " << get_numeric_value(d) << '\n';
   }

   void basic_quantity_test3()
   {
      auto constexpr t_s = pqs::imperial::time::s<>{10};
      pqs::imperial::time::min<> min = t_s;
      std::cout << get_numeric_value(min) <<'\n';
      QUAN_CHECK(( get_numeric_value(min) == 10./(60) ))
      pqs::imperial::time::hr<> hr = t_s;
      std::cout << get_numeric_value(hr) <<'\n';
      QUAN_CHECK(( get_numeric_value(hr) == 10./(60*60) ))
   }

   void basic_quantity_multiply_test()
   {
      auto q_si1 = pqs::si::length::m<>{10};
      auto q_si2 = pqs::si::length::mm<>{321};
      auto q_sir = q_si1 * q_si2;
      QUAN_CHECK( (get_numeric_value(q_sir) == 3210))
      std::cout << "result of mux = "  << get_numeric_value(q_sir) <<'\n';

      pqs::basic_quantity<
         pqs::si::proper_unit<
            pqs::exp_length<-1>,
            pqs::exponent10<-1>
         >
      > q_si3{2};
      auto r1 = q_si1 * q_si3;
      QUAN_CHECK( (r1 == 2.))
      std::cout << "result of dimless mux = "  << r1 <<'\n'; 

      pqs::si::length::ft<> uc1 = q_si1;
      auto q_ucr = uc1 * q_si2; 
      std::cout << "result of mux1 = "  << get_numeric_value(q_ucr) <<'\n';  
   }

   using namespace pqs;

   void check_conversion_factor_test()
   {

   using Qb = si::length::m<>;
   using Q  = si::length::ft<>;

   static_assert( evaluate<get_conversion_factor<Qb> >() == 1 );
   static_assert( evaluate<get_conversion_factor<Q> >() != 1 );

   constexpr dimensionless_quantity n = -12345.678;
   
   constexpr Q  q{n};
   constexpr Qb qB = q;

   static_assert( 
      get_numeric_value(qB) == 
         get_numeric_value(q) * evaluate<get_conversion_factor<Q> >() 
   );

   }
}

void basic_quantity_test()
{
   basic_quantity_test1();
   basic_quantity_test2();
   basic_quantity_test3();
   check_conversion_factor_test();
   basic_quantity_multiply_test();
}