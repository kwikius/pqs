

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>
#include <pqs/bits/quantity.hpp>
#include "../test/make_quantity.hpp"

using pqs::make_quantity;

namespace expo{

   constexpr pqs::exp_length<1> length;
   constexpr pqs::exp_time<1> time;
   constexpr pqs::exp_mass<1> mass;

   constexpr auto velocity = length / time;

   constexpr auto acceleration = velocity / time;
   struct force_t : decltype(mass * acceleration) {};
   force_t force;

   // derived_abstract_quantity ?
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
   static_assert(is_base_quantity_exp(expo::length),"");
   static_assert(is_abstract_quantity(expo::length),"");

   static_assert(is_base_quantity_exp(expo::mass),"");
   static_assert(is_abstract_quantity(expo::mass),"");

   static_assert(is_base_quantity_exp(expo::time),"");
   static_assert(is_abstract_quantity(expo::time),"");

   static_assert(is_dimension(expo::velocity),"");
   static_assert(is_abstract_quantity(expo::velocity),"");
   static_assert(not is_derived_dimension(expo::velocity),"");

   static_assert(is_derived_dimension(expo::vertical_velocity),"");
   static_assert(is_abstract_quantity(expo::vertical_velocity ),"");

   constexpr auto q1 = make_quantity<3>(expo::length,20.0);
   constexpr auto q2 = make_quantity<3>(expo::acceleration,20.0);
   constexpr auto q3 = make_quantity<3>(expo::vertical_velocity,20.0);
   constexpr auto q4 = make_quantity<3>(expo::force,20.0);

   //################################################
   // Error: Should not be accepted, as the abstract_quantity universe knows nothing of this type
   auto q5 = make_quantity<3>(double{},20.0);
  //##################################################
   // OK dimensionless quantity : should probably return a real
   auto q6 = make_quantity<3>(pqs::dimension<>{},20.0);
  //##################################################

   static_assert ( not is_abstract_quantity(q1),"");
   static_assert ( not is_abstract_quantity(q2),"");
   static_assert ( not is_abstract_quantity(q3),"");
   static_assert ( not is_abstract_quantity(q4),"");

   // uncomment for error messages
   q5 = q5;
}
