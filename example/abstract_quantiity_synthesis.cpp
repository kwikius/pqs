

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>
#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/bits/quantity.hpp>
#include "make_quantity.hpp"

using pqs_exposition::exp;
using pqs::base_length;
using pqs::base_time;
using pqs::base_mass;

namespace exposition{

   // base_quantity exponent aka base_dimension exponent
   constexpr exp<base_length,1> length;
   constexpr exp<base_time,1> time;
   constexpr exp<base_mass,1> mass;

   // dimension<exp<base_length,1>,exp<base_time,-1> >
   constexpr auto velocity = length / time;

   // derived_dimension
   struct vertical_velocity_t : decltype(velocity) {};
   constexpr vertical_velocity_t  vertical_velocity ;
}

namespace {

   template <typename T>
   struct is_abstract_quantity_t :
      pqs::meta::or_<
        pqs::is_base_quantity_exp<T>,
        pqs::is_dimension<T>,
        pqs::is_derived_dimension<T>
      >{};

   template <typename T>
   constexpr bool is_abstract_quantity(T t)
   {
      return is_abstract_quantity_t<T>::value;
   }

   template <typename T> 
   constexpr bool is_base_quantity_exp(T t)
   {
      return pqs::is_base_quantity_exp<T>::value;
   }

   template <typename T> 
   constexpr bool is_dimension(T t)
   {
      return pqs::is_dimension<T>::value;
   }

   template <typename T> 
   constexpr bool is_derived_dimension(T t)
   {
      return pqs::is_derived_dimension<T>::value;
   }
}

int main()
{ 
   static_assert(is_base_quantity_exp(exposition::length),"");
   static_assert(is_abstract_quantity(exposition::length),"");

   static_assert(is_base_quantity_exp(exposition::mass),"");
   static_assert(is_abstract_quantity(exposition::mass),"");

   static_assert(is_base_quantity_exp(exposition::time),"");
   static_assert(is_abstract_quantity(exposition::time),"");

   static_assert(is_dimension(exposition::velocity),"");
   static_assert(is_abstract_quantity(exposition::velocity),"");
   static_assert(not is_derived_dimension(exposition::velocity),"");

   static_assert(is_derived_dimension(exposition::vertical_velocity),"");
   static_assert(is_abstract_quantity(exposition::vertical_velocity ),"");

   constexpr auto q1 = make_quantity<3>(exposition::length,20.0);
   constexpr auto q2 = make_quantity<3>(exposition::velocity,20.0);
   constexpr auto q3 = make_quantity<3>(exposition::vertical_velocity,20.0);

   static_assert ( not is_abstract_quantity(q1),"");
   static_assert ( not is_abstract_quantity(q2),"");
   static_assert ( not is_abstract_quantity(q3),"");

  // int x = exposition::velocity;
}
