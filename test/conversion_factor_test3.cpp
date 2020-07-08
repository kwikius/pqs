



#include <pqs/type_templates/conversion_factor.hpp>

#include <iostream>

using namespace pqs;

namespace pqs{

   template <intmax_t N, intmax_t D>
   std::ostream & operator << (std::ostream & os, std::ratio<N,D> )
   {
      using r = std::ratio<N,D>;
      return os << "{ " << r::num << " / " << r::den << " }" ;
   }

   template <int N, int D>
   std::ostream & operator << (std::ostream & os, pqs::exponent10<N,D> )
   {
      using r = typename pqs::exponent10<N,D>::ratio;
      return os << "( " << r::num << " / " << r::den << " )" ;
   }

   template <typename M, typename E>
   std::ostream & operator << (std::ostream & os, conversion_factor<M,E> v)
   {
      return os << typename decltype(v)::multiplier{} << " ^ " << typename decltype(v)::exponent{} ;
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
}   

namespace {

   void cf_times_rat_test()
   {
      using cf1 = conversion_factor< 
         std::ratio<1>, exponent10<3,1> 
      >;
      using res = decltype(cf1{} * std::ratio<2>{});
      static_assert(is_conversion_factor<res>);
      static_assert( std::is_same_v<res::multiplier ,std::ratio<2> > );
      static_assert( std::is_same_v<res::exponent , exponent10<3> > );

      using res1 = decltype( std::ratio<2>{} * cf1{} );
      static_assert(is_conversion_factor<res1>);
      static_assert( std::is_same_v<res1::multiplier ,std::ratio<2> > );
      static_assert( std::is_same_v<res1::exponent , exponent10<3> > );
   }

   void cf_exp10_rat_test()
   {
      using cf1 = decltype(std::ratio<123,456>{} ^ exponent10<-2,3>{});
      std::cout << "cf1 = " << cf1{} <<'\n';
      static_assert( std::is_same_v<cf1::multiplier ,std::ratio<205,76> > );
      static_assert( std::is_same_v<cf1::exponent , exponent10<-5,3> > );

   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void conversion_factor_test3()
#endif
{
   cf_times_rat_test();
   cf_exp10_rat_test();
}
