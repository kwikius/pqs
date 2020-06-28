#include "test.hpp"
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/base_quantities.hpp>

struct my_rat{
  constexpr my_rat( int n , int d) : num{n},den{d} {}
  int num;
  int den;
};

struct my_exp10{
  constexpr my_exp10( int n , int d) : num{n},den{d} {}
  int num;
  int den;
};

struct my_cf{
   constexpr my_cf( my_rat m, my_exp10 e) : mux{m},exp(e){}
   my_rat mux;
   my_exp10 exp;
};

constexpr my_cf operator*( my_rat m, my_exp10 e)
{
   return my_cf(m,e);
}

#include <iostream>

#if defined __cpp_nontype_template_args
template<my_cf cf>
void print()
{
   std::cout << "[" << cf.mux.num << "/" << cf.mux.den << "] * 10^(" << cf.exp.num << "/" << cf.exp.den << ")";
}

template < auto D>
inline constexpr void testd()
{
   std::cout << "huh!\n";
   if constexpr ( pqs::dimension<decltype(D)> ){
      std::cout << "dimension\n";
   }

   if constexpr ( pqs::base_quantity_exponent<decltype(D)> ){
      std::cout << "exp\n";
   }

}

#endif


#if defined PQS_STANDALONE

int errors =0;
int main()
#else
void sandbox()
#endif
{
#if defined __cpp_nontype_template_args

   print<my_cf(my_rat(1,2),my_exp10(2,3))>();
   print<my_rat(1,3) * my_exp10(3,4)>();

   std::cout <<'\n';
   testd<pqs::da_length<> / pqs::da_time<> * pqs::da_mass<> >();
   std::cout << '\n';

   testd<pqs::da_length<> >();
   std::cout << '\n';
      
#endif
}
