#include "test.hpp"
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/instance/basic_quantity.hpp>

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

template<my_cf cf>
void print()
{
   std::cout << "[" << cf.mux.num << "/" << cf.mux.den << "] * 10^(" << cf.exp.num << "/" << cf.exp.den << ")" <<'\n';
}

template <auto D>
  requires pqs::dimension<decltype(D)>
inline constexpr void testd()
{
   using d = decltype(D);
   if constexpr ( pqs::is_simple_dimension_list<d> ){
      std::cout << "dimension list\n";
   }else {
      if constexpr ( pqs::base_quantity_exponent<d> ){
         std::cout << "base_quantity_exp\n";
      }else{
         if constexpr (pqs::is_custom_base_quantity_exp<d> ){
            std::cout << "custom base_quantity_exp\n";
         } else{
            if constexpr (pqs::is_custom_dimension_list<d> ){
               std::cout << "custom dimension_list\n";
            }
         }
      }
   }

}

namespace {

   struct my_abstract_acceleration : decltype( pqs::abstract_length<> / pqs::abstract_time<> ) {} ;

   struct my_abstract_time : decltype( pqs::abstract_time<> ) {};

   struct si_sys{};

   template <
      typename S,
      auto D,
      auto CF
   > struct unit1 {
      using conversion_factor = decltype(CF);
    };
         
}

namespace pqs{ namespace impl{
   

//   > struct is_conversion_factor_impl<unit1<S,D,CF> > : std::true_type{};

}}

#if defined PQS_STANDALONE

int errors =0;
int main()
#else
void sandbox()
#endif
{
   print<my_cf(my_rat(1,2),my_exp10(2,3))>();
   print<my_rat(1,3) * my_exp10(3,4)>();

//   testd<pqs::abstract_length<> >();                                    // base quantity exp
   testd<pqs::abstract_length<> / pqs::abstract_time<> * pqs::abstract_mass<> >();  // dimension_list

   testd<my_abstract_acceleration{}>();                                           // custom dimension_list     
   testd<my_abstract_time{}>(); 


  int x = pqs::abstract_length<> * pqs::abstract_time<> / pqs::abstract_mass<> ;

}
