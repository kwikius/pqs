
#include "test.hpp"

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>
#include <pqs/bits/quantity.hpp>
#include <pqs/meta/type_list.hpp>
#include <pqs/bits/quantity.hpp>
#include <pqs/bits/dimension.hpp>

namespace {

   constexpr pqs::exp_length<1> length;  // base_dimension_exp

   struct named_length_t : decltype(length) {};  // custom_dimension

   constexpr pqs::exp_time<1> q_time;      // base_dimension_exp
   constexpr pqs::exp_mass<1> mass;      // base_dimension_exp

   constexpr auto velocity = length / q_time;  // base_quantity_exp_list

   constexpr auto acceleration = velocity / q_time;     // base_quantity_exp_list
   struct : decltype(mass * acceleration) {   // custom_dimension
   } force;

   struct : decltype(velocity) {  // anonymous class custom_dimension
   } vertical_velocity ;

   constexpr auto mux_test = vertical_velocity * q_time * length ;
   constexpr auto div_test = vertical_velocity / q_time ;

   constexpr auto velocity1 = named_length_t{} / q_time;  // base_quantity_exp_list

   constexpr auto area = pqs::pow<2,1>(length);  // base_quantity_exp,2,1

   constexpr auto velocity2 = pqs::pow<2,1>(velocity);

   constexpr auto length_pow_1_2 = pqs::pow<1,2>(named_length_t{});

   //TODO need a consistent way to deal with dimensionless
   // struct dimensionless ?
   // also need dimensionless / d --> inverse(d)
   // dimensionless * d --> d
   constexpr auto dimless1 = acceleration / acceleration; // list<>
   constexpr auto dimless2 = q_time/q_time;   // exp_time<0>
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
   constexpr bool same_no_cr = std::is_same_v<
      std::remove_cv_t<std::remove_reference_t<T1> >,
      std::remove_cv_t<std::remove_reference_t<T2> >
   >;
}

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else

void dimension_test2()
#endif
{ 
   static_assert(same_no_cr<decltype(length),pqs::exp_length<1> >,"");
   static_assert(is_base_quantity_exp(length),"");
   static_assert(is_dimension(length),"");

   static_assert(same_no_cr<
            decltype(velocity),
            pqs:: base_quantity_exp_list<pqs::exp_length<1>,pqs::exp_time<-1> >
   >,"");
   static_assert(is_base_quantity_exp_list(velocity),"");
   static_assert(is_dimension(velocity),"");
   static_assert(not is_derived_dimension(velocity),"");

   static_assert(same_no_cr<decltype(mass),pqs::exp_mass<1> >,"");
   static_assert(is_base_quantity_exp(mass),"");
   static_assert(is_dimension(mass),"");

   static_assert(is_base_quantity_exp(q_time),"");
   static_assert(is_dimension(q_time),"");

   static_assert(is_derived_dimension(vertical_velocity),"");
   static_assert(is_dimension(vertical_velocity ),"");
   static_assert(same_no_cr<
            decltype(velocity),
            decltype(vertical_velocity)::base_exponent_type
   >,"");

   static_assert(is_base_quantity_exp_list(velocity2),"");

 #if defined PQS_STANDALONE
   EPILOGUE
#endif 

}
