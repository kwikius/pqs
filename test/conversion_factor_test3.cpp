
#include "test.hpp"

#include <pqs/types/conversion_factor.hpp>
#include <iostream>
#include <iomanip>

using namespace pqs;

namespace pqs{

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
   std::ostream & operator << (std::ostream & os, conversion_factor<M,E> v)
   {
      return os << typename decltype(v)::multiplier{} << "*10^" << typename decltype(v)::exponent{} ;
   }

   template <typename CFL, typename CFR>
   inline constexpr bool same_cf()
   {
      return evaluate<CFL>() == evaluate<CFR>() ;
   }

   template <typename CF>
   void show_cf()
   {
      std::cout << CF{} << " == " << evaluate<CF>() ;
   }

} //pqs   

namespace {

   void cf_times_rat_test()
   {
      using cf1 = conversion_factor< 
         std::ratio<1>, exponent10<3> 
      >;
     // std::cout<< "cf1 = " << cf1{} <<'\n';
      using res1 = decltype( cf1{} * std::ratio<2>{} );

     // std::cout << "res1 = " << res1{} <<'\n';
      static_assert(is_conversion_factor<res1>);
      static_assert( std::is_same_v<res1::multiplier ,std::ratio<2> > );
      static_assert( std::is_same_v<res1::exponent , exponent10<3> > );

      using res2 = decltype( std::ratio<10>{} * res1{} );
   //   std::cout << "res2 = " << res2{} <<'\n';
      static_assert(is_conversion_factor<res2>);
      static_assert( std::is_same_v<res2::multiplier ,std::ratio<2> > );
      static_assert( std::is_same_v<res2::exponent , exponent10<4> > );

      using res3 = decltype( res1{} / std::ratio<2>{} );
     // std::cout << "res3 = " << res3{} <<'\n';
      static_assert(is_conversion_factor<res3>);
      static_assert( std::is_same_v<res3::multiplier ,std::ratio<1> > );
      static_assert( std::is_same_v<res3::exponent , exponent10<3> > );

      using res4 = decltype( std::ratio<2>{} / res3{} );
     // std::cout << "res4 = " << res4{} <<'\n';
      static_assert(is_conversion_factor<res4>);
      static_assert( std::is_same_v<res4::multiplier ,std::ratio<2> > );
      static_assert( std::is_same_v<res4::exponent , exponent10<-3> > );

      using res5 = decltype( res2{} / std::ratio<3>{} );
     // std::cout << "res5 = " << res5{} <<'\n';
      static_assert(is_conversion_factor<res5>);
      static_assert( std::is_same_v<res5::multiplier ,std::ratio<20,3> > );
      static_assert( std::is_same_v<res5::exponent , exponent10<3> > );
   }

   void rat_exp10_test()
   {
      using cf1 = decltype( std::ratio<123,456>{} ^ exponent10<-2,3>{} );
     // std::cout << "cf1 = " << cf1{} <<'\n';
      static_assert( std::is_same_v<cf1::multiplier ,std::ratio<205,76> > );
      static_assert( std::is_same_v<cf1::exponent , exponent10<-5,3> > );
   }

   void cf_exp10_test()
   {
       using cf1 = decltype(std::ratio<23,11>{} ^ exponent10<6>{} );

      // std::cout << "cf1 = " << cf1{} <<'\n';
       static_assert(is_conversion_factor<cf1>);
       static_assert( std::is_same_v<cf1::multiplier ,std::ratio<23,11> > );
       static_assert( std::is_same_v<cf1::exponent , exponent10<6> > );

       using res1 = decltype( cf1{} ^ exponent10<1,2>{} );
     //  std::cout << "res1 = " << res1{} <<'\n';
       static_assert(is_conversion_factor<res1>);
       static_assert( std::is_same_v<res1::multiplier ,std::ratio<23,11> > );
       static_assert( std::is_same_v<res1::exponent , exponent10<3> > ); 
   }

   void conversion_factor_example()
   {
      auto constexpr pi = std::ratio<314159265358979>() ^ exponent10<-14>();

      static_assert(is_conversion_factor<decltype(pi)> );
      constexpr auto v1 = evaluate(pi);             // object form
      constexpr auto v2 = evaluate<decltype(pi)>(); // type argument form

      static_assert( v1 == v2 );  // both forms are equivalent

    //  std::cout << std::setprecision(16) << " pi = " << v1 << '\n';

   }
   // pi = 3.14159265358979
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void conversion_factor_test3()
#endif
{
   cf_times_rat_test();
   rat_exp10_test();
   cf_exp10_test();
   conversion_factor_example();
}
