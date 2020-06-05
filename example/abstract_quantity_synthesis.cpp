

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>
#include <pqs/bits/quantity.hpp>
#include "../test/make_quantity.hpp"

using pqs::make_quantity;

namespace expo{

   constexpr pqs::exp_length<1> length;  // base_dimension_exp

   struct named_length_t : decltype(length) {};  // custom_dimension

   constexpr pqs::exp_time<1> time;      // base_dimension_exp
   constexpr pqs::exp_mass<1> mass;      // base_dimension_exp

   constexpr auto velocity = length / time;  // base_quantity_exp_list

   constexpr auto acceleration = velocity / time;     // base_quantity_exp_list
   struct force_t : decltype(mass * acceleration) {   // custom_dimension
   };  // custom_dimension
   force_t force;

   // derived_abstract_quantity?
   struct vertical_velocity_t : decltype(velocity) {  // custom_dimension
   };

   struct : decltype(velocity) {  // custom_dimension
   } vertical_velocity ;

   constexpr auto mux_test = vertical_velocity * time * length ;
   constexpr auto div_test = vertical_velocity / time ;

   constexpr auto velocity1 = named_length_t{} / time;  // base_quantity_exp_list

   // need a way to deal with dimensionless
   constexpr auto dimless1 = acceleration / acceleration; // list<>
   constexpr auto dimless2 = time/time;   // exp_time<0>
   constexpr auto dimless3 = named_length_t{} / named_length_t{}; // length<0>
   constexpr auto dimless4 = named_length_t{} / length; // length<0>
   constexpr auto dimless5 = vertical_velocity / vertical_velocity; // list<>
}

namespace {

   template <typename T>
   constexpr bool is_dimension(T t)
   {
      return pqs::is_dimension<T>::value;
   }

   template <typename T> 
   constexpr bool is_base_quantity_exp(T t)
   {
      return pqs::is_base_quantity_exp<T>::value;
   }

   template <typename T> 
   constexpr bool is_base_quantity_exp_list(T t)
   {
      return pqs::is_base_quantity_exp_list<T>::value;
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
   static_assert(is_dimension(expo::length),"");

   static_assert(is_base_quantity_exp(expo::mass),"");
   static_assert(is_dimension(expo::mass),"");

   static_assert(is_base_quantity_exp(expo::time),"");
   static_assert(is_dimension(expo::time),"");

   static_assert(is_base_quantity_exp_list(expo::velocity),"");
   static_assert(is_dimension(expo::velocity),"");
   static_assert(not is_derived_dimension(expo::velocity),"");

   static_assert(is_derived_dimension(expo::vertical_velocity),"");
   static_assert(is_dimension(expo::vertical_velocity ),"");

   constexpr auto q1 = make_quantity<3>(expo::length,20.0);
   constexpr auto q2 = make_quantity<3>(expo::acceleration,20.0);
   constexpr auto q3 = make_quantity<3>(expo::vertical_velocity,20.0);
   constexpr auto q4 = make_quantity<3>(expo::force,20.0);

   //################################################
   // Error: Should not be accepted, as the abstract_quantity universe knows nothing of this type
   auto q5 = make_quantity<3>(double{},20.0);
  //##################################################
   // OK dimensionless quantity : should probably return a real
   auto q6 = make_quantity<3>(pqs::base_quantity_exp_list<>{},20.0);
  //##################################################

   static_assert ( not is_dimension(q1),"");
   static_assert ( not is_dimension(q2),"");
   static_assert ( not is_dimension(q3),"");
   static_assert ( not is_dimension(q4),"");

   // uncomment for error messages
   int x = expo::vertical_velocity_t{};
}
