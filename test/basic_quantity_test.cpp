#include "test.hpp"

// test interaction with time.h
#include <time.h>
#include <pqs/si/length.hpp>
#include <pqs/si/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/imperial/time.hpp>
#include <pqs/bits/quantity_output.hpp>

#include <iomanip>
#include <iostream>

struct dummy_system{ 

   typedef dummy_system type; 
};

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<
         ::dummy_system
      > : std::true_type{};
   }
}

namespace {

   template <intmax_t N, intmax_t D>
   constexpr
   std::ostream & operator << (std::ostream & os, std::ratio<N,D> )
   {
      using r = std::ratio<N,D>;
      if constexpr ( r::den == 1)
         return os  << r::num ;
      else 
         return os << "(" << r::num << "/" << r::den << ")" ;
   }

   template <int N, int D>
   constexpr
   std::ostream & operator << (std::ostream & os, pqs::exponent10<N,D> )
   {
      using r = typename pqs::exponent10<N,D>::ratio;
      if constexpr ( r::den ==1) 
         return os << r::num;
      else
         return os << "(" << r::num << "/" << r::den << ")" ;

   }

   template <typename M, typename E>
   std::ostream & operator << (std::ostream & os, pqs::conversion_factor<M,E> v)
   {
      return os << typename decltype(v)::multiplier{} << "*10^" << typename decltype(v)::exponent{} ;
   }
}

using namespace pqs;

namespace {

   void basic_quantity_concept_test()
   {
      static_assert(pqs::is_defined<double>,"");
      pqs::basic_quantity<
         pqs::basic_unit<
            dummy_system,
            decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
            decltype( std::ratio<30,2>{} ^ pqs::exponent10<3>{})
         >, double
      > constexpr q{20.0};

      using U = pqs::get_unit<decltype(q)>;

      QUAN_CHECK(( ! pqs::si::is_normative_unit<U> ))
         
      using D = pqs::get_dimension<decltype(q)>;

      using V = pqs::get_numeric_type<decltype(q)>;

      using Cf = pqs::get_conversion_factor<decltype(q)>;

      using Sm = pqs::get_measurement_system<decltype(q)>;

      auto constexpr v = get_numeric_value(q);
     
      std::cout << " qs numeric value = " << v << '\n';

      QUAN_CHECK(( v == 20.0 ))

      auto constexpr r = q + q;

      QUAN_CHECK(( get_numeric_value(r) == 40.0))
   }

   void basic_quantity_add_test()
   {
      auto q1 = pqs::si::length::m<>{1};
      QUAN_CHECK(( pqs::si::is_normative_unit<pqs::get_unit<decltype(q1)> > ))

      auto q2 = pqs::si::length::mm<>{321};
      QUAN_CHECK(( pqs::si::is_normative_unit<pqs::get_unit<decltype(q1)> > ))

      auto q3 = q1 + q2;
      QUAN_CHECK( (get_numeric_value(q3) == 1321))

      std::cout << "q3 numeric value = " << get_numeric_value(q3) << '\n';

      auto q4 = pqs::si::length::ft<>{6};
      auto q5 = q1 + q4;
      QUAN_CHECK(( pqs::si::is_normative_unit<pqs::get_unit<decltype(q5)> > ))
      std::cout << "q5 numeric value = " << get_numeric_value(q5) << '\n';

      using Cf5 = pqs::get_conversion_factor<decltype(q5)>;

      QUAN_CHECK(( std::is_same_v< 
         Cf5, pqs::conversion_factor<std::ratio<1>,pqs::exponent10<-1> >
      > ))

      auto q6 = pqs::imperial::length::ft<>{1};
      auto q7 = pqs::imperial::length::yd<>{2};
      auto q8 = q6 + q7;
      QUAN_CHECK( (get_numeric_value(q8) == 7))
      std::cout << " imp numeric value = " << get_numeric_value(q8) << '\n';
   }

   void basic_quantity_imperial_test()
   {
      auto constexpr q1 = pqs::imperial::time::s<>{10};
      pqs::imperial::time::min<> q2 = q1;
      std::cout << get_numeric_value(q2) <<'\n';
      QUAN_CHECK(( get_numeric_value(q2) == 10./(60) ))
      pqs::imperial::time::hr<> q3 = q1;
      std::cout << get_numeric_value(q3) <<'\n';
      QUAN_CHECK(( get_numeric_value(q3) == 10./(60*60) ))
   }

   void basic_quantity_multiply_test()
   {
      auto q1 = pqs::si::length::m<>{10};
      auto q2 = pqs::si::length::mm<>{321};

      using U1 = pqs::get_unit<decltype(q1)>;

      QUAN_CHECK(( pqs::si::is_normative_unit<U1> ))

      auto q3 = q1 * q2;
      QUAN_CHECK( (get_numeric_value(q3) == 3210))
      std::cout << "result of mux = "  << get_numeric_value(q3) <<'\n';

      pqs::basic_quantity<
         pqs::si::normative_unit<
            pqs::exp_length<-1>,
            pqs::exponent10<-1>
         >
      > q4{2};
      auto v1 = q1 * q4;
      QUAN_CHECK( (v1 == 2.))
      std::cout << "result of dimless mux = "  << v1 <<'\n'; 

      pqs::si::length::ft<> q5 = q1;
      using U5 = pqs::get_unit<decltype(q5)>;
      QUAN_CHECK(( not pqs::si::is_normative_unit<U5> ))

      auto q6 = q5 * q2; 
      QUAN_CHECK(( pqs::si::is_normative_unit<pqs::get_unit<decltype(q6)> > ))
      std::cout << "result of mux1 = "  << get_numeric_value(q6) <<'\n';  
   }

   void basic_quantity_divide_test()
   {
      // dimensionless
      auto q1 = pqs::si::length::m<>{10};
      auto q2 = pqs::si::length::mm<>{10000};
      auto v1 =  q1 / q2;
      QUAN_CHECK(( v1 == 1 ))
      std::cout << "result of div = "  << v1 <<'\n';

      auto q4 = pqs::si::time::s<>{5};

      auto q5 = q1 / q4;
      QUAN_CHECK(( get_numeric_value(q5) == 2 ))
      std::cout << "result of div1 = "  << get_numeric_value(q5) <<'\n';

      pqs::si::time::min<> q6 = q4;
      std::cout << "q6 cf = " << get_conversion_factor<decltype(q6)>() << '\n';
      QUAN_CHECK(( not pqs::si::is_normative_unit<pqs::get_unit<decltype(q6)> > ))

      auto q7 = q1 / q6;
      QUAN_CHECK(( pqs::si::is_normative_unit<pqs::get_unit<decltype(q7)> > ))
      std::cout << "q7 cf = " << get_conversion_factor<decltype(q7)>() << '\n';
      std::cout << "q7 = "  << get_numeric_value(q7) <<'\n';
      QUAN_CHECK(( get_numeric_value(q7) == 0.02 ))
   }

   void scalar_multiply_test()
   {
      auto q1 = pqs::si::length::m<>{10};
      auto q2 = pqs::si::length::mm<>{10000};

      auto q1a = q1 * 2.0;
      QUAN_CHECK(( get_numeric_value(q1a) == 20 ))

      auto q2a = 3.0 * q2;
      QUAN_CHECK(( get_numeric_value(q2a) == 30000 ))
      static_assert(std::is_same_v<decltype(q1),decltype(q1a)>);
      static_assert(std::is_same_v<decltype(q2),decltype(q2a)>);
   }

   using namespace pqs;

   // wiki example
   void conversion_factor_semantic_test()
   {
      using Qb = si::length::m<>;
      using Q  = si::length::ft<>;

      static_assert( same_measurement_system<Q,Qb> );
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

   void output_test()
   {
      auto constexpr q1 = si::length::m<>{100};
      si::length::ft<> constexpr q2 = q1;

      std::cout << std::setprecision(7);
      std::cout << "****************************\n";
      output<pqs::charset_utf8>( std::cout, q1);
      std::cout << " == " ;
      output< pqs::charset_utf8>( std::cout, q2);
      std::cout  << '\n';
      std::cout << "****************************\n";
      
   }
}

void basic_quantity_test()
{
   basic_quantity_concept_test();
   basic_quantity_add_test();
   basic_quantity_imperial_test();
   conversion_factor_semantic_test();
   basic_quantity_multiply_test();
   basic_quantity_divide_test();
   output_test();
   scalar_multiply_test();
}