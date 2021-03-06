
#include "test.hpp"
#include <pqs/bits/meta/strip_cr.hpp>
#include <pqs/types/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/concepts/quantity.hpp>

namespace {

   constexpr pqs::exp_length<1> length;  // base_dimension_exp

   struct named_length_t : decltype(length) {};  // custom_dimension

   constexpr pqs::exp_time<1> time_;      // base_dimension_exp time_ to avoid global c time() function in 
   constexpr pqs::exp_mass<1> mass;      // base_dimension_exp

   constexpr auto velocity = length / time_;  // dimension_list

   constexpr auto acceleration = velocity / time_;     // dimension_list
   struct : decltype(mass * acceleration) {   // custom_dimension
   } force;

   struct : decltype(velocity) {  // anonymous class custom_dimension
   } vertical_velocity ;

   typedef decltype(vertical_velocity) vvtype;
   static_assert( pqs::dimension<vvtype>,"");
   static_assert( pqs::dimension<pqs::get_simple_dimension<vvtype> >,"");
   static_assert( pqs::is_custom_dimension<vvtype>,"");

   constexpr auto mux_test = vertical_velocity * time_ * length ;
   constexpr auto div_test = vertical_velocity / time_ ;

   constexpr auto velocity1 = named_length_t{} / time_;  // dimension_list

   constexpr auto area = pqs::pow<2,1>(length);  // base_quantity_exp,2,1

   constexpr auto velocity2 = pqs::pow<2,1>(velocity);

   constexpr auto length_pow_1_2 = pqs::pow<1,2>(named_length_t{});

   constexpr auto dimless1 = acceleration / acceleration; //  dimensionless
   constexpr auto dimless2 = time_/time_;   // dimensionless
   constexpr auto dimless3 = named_length_t{} / named_length_t{}; // dimensionless
   constexpr auto dimless4 = named_length_t{} / length; // dimensionless
   constexpr auto dimless5 = vertical_velocity / vertical_velocity; // dimensionless

   //TODO comparison ops == and !=
   template <typename T>
   constexpr bool is_dimension(T t)
   {
      return pqs::dimension<T>;
   }

   template <typename T> 
   constexpr bool is_base_quantity_exponent(T t)
   {
      return pqs::base_quantity_exponent<T>;
   }

   template <typename T> 
   constexpr bool is_dimension_list(T t)
   {
      return pqs::is_dimension_list<T>;
   }

   template <typename T> 
   constexpr bool is_custom_dimension(T t)
   {
      return pqs::is_custom_dimension<T>;
   }

   template <typename T1, typename T2>
   struct same_no_cr : std::is_same<
      std::remove_cvref_t<T1>,
      std::remove_cvref_t<T2>
   >{};

   void equality_test()
   {
      static_assert(length == length);
      static_assert((length != length) == false);
      static_assert(length == named_length_t());
      static_assert( (length == time_) == false);
      static_assert( force == mass * acceleration);
      static_assert( force != mass * acceleration * time_);
   }
}

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else
void dimension_test2()
#endif
{ 
   equality_test();
   static_assert(same_no_cr<decltype(length),pqs::exp_length<1> >::value,"");
   static_assert(is_base_quantity_exponent(length),"");
   static_assert(is_dimension(length),"");

   static_assert(
      same_no_cr<
         decltype(velocity),
         pqs:: dimension_list<pqs::exp_length<1>,pqs::exp_time<-1> >
      >::value,"");
   static_assert(is_dimension_list(velocity),"");
   static_assert(is_dimension(velocity),"");
   static_assert(not is_custom_dimension(velocity),"");

   static_assert(same_no_cr<decltype(mass),pqs::exp_mass<1> >::value,"");
   static_assert(is_base_quantity_exponent(mass),"");
   static_assert(is_dimension(mass),"");

   static_assert(is_base_quantity_exponent(time_),"");
   static_assert(is_dimension(time_),"");

   static_assert(is_custom_dimension(vertical_velocity),"");
   static_assert(is_dimension(vertical_velocity ),"");
   static_assert(same_no_cr<
            decltype(velocity),
            decltype(vertical_velocity)::simple_dimension
   >::value,"");

   static_assert(is_dimension_list(velocity2),"");

   static_assert(same_no_cr<decltype(dimless1),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless2),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless3),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless4),pqs::dimensionless>::value,"");
   static_assert(same_no_cr<decltype(dimless5),pqs::dimensionless>::value,"");


 #if defined PQS_STANDALONE
   EPILOGUE
#endif 

}
