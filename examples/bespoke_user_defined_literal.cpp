
/*
  UDT function that returns the type with smallest footprint
  so for example
  127_my_type would return an underlying type of signed char etc
  Working for ints. TODO min_float
*/
#include <iostream>
#include <string>
#include <limits>
#include <type_traits>

#include <pqs/bits/meta/eval_if.hpp>
#include <pqs/bits/meta/identity.hpp>
#include <pqs/bits/meta/is_narrowing_conversion.hpp>

namespace meta = pqs::meta;

template <typename T>
struct my_type{
   constexpr my_type( T const & v): val{v}{}
   T val;

   template <typename T1>
      requires !meta::is_narrowing_conversion<T, T1>
   constexpr operator my_type<T1>() const { return {val};}

};

struct undefined;

/*
  return type of min sized int that can hold V
*/
template <unsigned long long V>
struct min_int{

   typedef typename meta::eval_if<
         std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int8_t>::max()))>,
      meta::identity<int8_t>, // https://github.com/kwikius/pqs/blob/master/src/include/pqs/bits/meta/identity.hpp
         std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int16_t>::max()))>,
      meta::identity<int16_t>,
         std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int32_t>::max()))>,
      meta::identity<int32_t>,
         std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int64_t>::max()))>,
      meta::identity<int64_t>,
      undefined
   >::type type;
};

template <unsigned long long V>
using min_int_t = typename min_int<V>::type;
//-- char digits ----------
template <char C > struct is_digit_impl;

template <char C >
  requires ( (C < '0') || ( C > '9') ) 
  struct is_digit_impl<C> : std::integral_constant<bool,false>{};

template <char C >
 requires ( (C >= '0') && ( C <= '9') ) 
  struct is_digit_impl<C> : std::integral_constant<bool,true>{};
template <char C> constexpr bool is_digit = is_digit_impl<C>::value;

enum class number_style { Int, Float, Undefined};

template <char... C>
struct get_number;

template <char... C>
struct get_int;

template <char Cf, char... C>
  requires is_digit<Cf>
struct get_int<Cf,C...>{
   static unsigned long long constexpr multiplier = 10ULL * get_int<C...>::multiplier;
   static unsigned long long constexpr value = 
      (static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0')) * multiplier + get_int<C...>::value;
};

template <char Cf>
   requires is_digit<Cf>
struct get_int<Cf>{
   static unsigned constexpr multiplier = 1U;
   static unsigned int constexpr value = static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0');
};

template<>
struct get_number<'.'>{
   static long double constexpr value = 0.0;
   static constexpr unsigned int multiplier = 1U;
   static constexpr number_style style = number_style::Float;
};

template<char C>
  requires is_digit<C>
struct get_number<C>{
   static constexpr auto value = get_int<C>::value;
   static constexpr unsigned int multiplier = 1U;
   static constexpr number_style style = number_style::Int;
};

long double constexpr shiftpoint( long double v){
   return v >= 1.0 ? shiftpoint(v / 10) : v;
};

template<char ...C>
struct get_number<'.',C...>{
   static long double constexpr value = shiftpoint( static_cast<long double>(get_int<C...>::value));
   static constexpr unsigned int multiplier = 1U;
   static constexpr number_style style = number_style::Float;
};

template<char Cf,char... C>
  requires is_digit<Cf> && (get_number<C...>::style == number_style::Float)
struct get_number<Cf,C...>{
   static long double constexpr value = get_int<Cf>::value * get_number<C...>::multiplier + get_number<C...>::value;
   static unsigned long long constexpr multiplier = get_number<C...>::multiplier * 10;
   static constexpr number_style style = number_style::Float;
};

template<char Cf,char... C>
  requires is_digit<Cf> && (get_number<C...>::style == number_style::Int)
struct get_number<Cf,C...>{
   static constexpr auto value = get_int<Cf,C...>::value;
   static constexpr number_style style = number_style::Int;
};

template <char... V>
auto constexpr operator "" _my_type()
{
    auto constexpr value = get_number<V...>::value;
    if constexpr (std::is_floating_point_v<decltype(value)>){
      if constexpr ( value < std::numeric_limits<float>::max() ){
         return my_type<float>{static_cast<float>(value)};
      }else if constexpr ( value < std::numeric_limits<double>::max()){
         return my_type<double>{static_cast<double> (value)};
      }else{
         return my_type<long double>{value};
      }
    }else{
       using number_type = min_int_t<value>;
       return my_type<number_type>(value);
    }
}

//#################################################

int main()
{
   auto x = 1_my_type;
   auto constexpr y = 20000_my_type;
   auto z = 65537_my_type;

   static_assert(std::is_same<decltype(x),my_type<int8_t> >::value,"");
   static_assert(std::is_same<decltype(y),my_type<int16_t> const >::value,"");
   static_assert(std::is_same<decltype(z),my_type<int32_t> >::value,"");

   z = x;  // OK
   z = y;  // Great!
   // x = z ;// Error!

   auto constexpr a = 120.345_my_type;
   static_assert(std::is_same<decltype(a),my_type<float> const>::value,"");

   auto  b = 6000.345_my_type;
   static_assert(std::is_same<decltype(b),my_type<float>>::value,"");

   b = x; // OK but gives warning
   b = y; // OK but gives warning
   b = z; // OK but gives warning

   my_type<double> c = b;

   c = x; // OK but gives warning
   c = y; // OK but gives warning
   c = z; // OK but gives warning

  // x = b; // error
}





