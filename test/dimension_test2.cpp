
#include "test.hpp"
#include <pqs/meta/strip_cr.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/bits/basic_quantity.hpp>

namespace {

   constexpr pqs::exp_length<1> length;  // base_dimension_exp

   struct named_length_t : decltype(length) {};  // custom_dimension

   constexpr pqs::exp_time<1> time_;      // base_dimension_exp time_ to avoid global c time() function in 
   constexpr pqs::exp_mass<1> mass;      // base_dimension_exp

   constexpr auto velocity = length / time_;  // base_quantity_exp_list

   constexpr auto acceleration = velocity / time_;     // base_quantity_exp_list
   struct : decltype(mass * acceleration) {   // custom_dimension
   } force;

   struct : decltype(velocity) {  // anonymous class custom_dimension
   } vertical_velocity ;

   constexpr auto mux_test = vertical_velocity * time_ * length ;
   constexpr auto div_test = vertical_velocity / time_ ;

   constexpr auto velocity1 = named_length_t{} / time_;  // base_quantity_exp_list

   constexpr auto area = pqs::pow<2,1>(length);  // base_quantity_exp,2,1

   constexpr auto velocity2 = pqs::pow<2,1>(velocity);

   constexpr auto length_pow_1_2 = pqs::pow<1,2>(named_length_t{});

   //TODO need a consistent way to deal with dimensionless
   // struct dimensionless ?
   // also need dimensionless / d --> inverse(d)
   // dimensionless * d --> d
   constexpr auto dimless1 = acceleration / acceleration; // list<>
   constexpr auto dimless2 = time_/time_;   // exp_time<0>
   constexpr auto dimless3 = named_length_t{} / named_length_t{}; // length<0>
   constexpr auto dimless4 = named_length_t{} / length; // length<0>
   constexpr auto dimless5 = vertical_velocity / vertical_velocity; // list<>

   //TODO comparison ops == and !=
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

   template <typename T1, typename T2>
   struct same_no_cr : std::is_same<
      typename pqs::meta::strip_cr<T1>::type ,
      typename pqs::meta::strip_cr<T2>::type 
   >{};
}

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else
void dimension_test2()
#endif
{ 
   static_assert(same_no_cr<decltype(length),pqs::exp_length<1> >::value,"");
   static_assert(is_base_quantity_exp(length),"");
   static_assert(is_dimension(length),"");

   static_assert(
      same_no_cr<
         decltype(velocity),
         pqs:: base_quantity_exp_list<pqs::exp_length<1>,pqs::exp_time<-1> >
      >::value,"");
   static_assert(is_base_quantity_exp_list(velocity),"");
   static_assert(is_dimension(velocity),"");
   static_assert(not is_derived_dimension(velocity),"");

   static_assert(same_no_cr<decltype(mass),pqs::exp_mass<1> >::value,"");
   static_assert(is_base_quantity_exp(mass),"");
   static_assert(is_dimension(mass),"");

   static_assert(is_base_quantity_exp(time_),"");
   static_assert(is_dimension(time_),"");

   static_assert(is_derived_dimension(vertical_velocity),"");
   static_assert(is_dimension(vertical_velocity ),"");
   static_assert(same_no_cr<
            decltype(velocity),
            decltype(vertical_velocity)::base_exponent_type
   >::value,"");

   static_assert(is_base_quantity_exp_list(velocity2),"");

   static_assert(same_no_cr<decltype(dimless1),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless2),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless3),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless4),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless5),pqs::dimensionless>::value,"");


 #if defined PQS_STANDALONE
   EPILOGUE
#endif 

}