
/*
  UDL function that returns the type with smallest footprint
  so for example
  127_my_type would return an underlying type of signed char etc

*/
#include <iostream>
#include <string>
#include <limits>
#include <type_traits>

#include <pqs/bits/meta/eval_if.hpp>
#include <pqs/bits/meta/identity.hpp>
#include <pqs/bits/meta/is_narrowing_conversion.hpp>

namespace meta = pqs::meta;

/**
  some udt
**/
template <typename T>
struct my_type{
   constexpr my_type(T const & v): val{v}{}
   T val;
   template <typename T1>
      requires std::numeric_limits<T>::digits
         <= std::numeric_limits<T1>::digits
   constexpr operator my_type<T1>() const { return static_cast<T1>(val);}
};

//represent undefined
struct undefined;

/**
 * return type of min sized int that can hold V
**/
template <unsigned long long V>
struct min_int{
   typedef typename meta::eval_if<
         std::integral_constant<bool,(V < static_cast<unsigned long long>(std::numeric_limits<int8_t>::max()))>,
      meta::identity<int8_t>,
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

template <char C> constexpr bool is_digit = (C >= '0') && ( C <= '9');

enum class number_style { Int, Float, Undefined};

template <char... C>
struct get_number;

template <char... C>
struct get_int;

template <char Cf, char... C>
  requires is_digit<Cf>
struct get_int<Cf,C...>{
   static unsigned long long constexpr multiplier = 10ULL * get_int<C...>::multiplier;
  // static constexpr unsigned int num_digits_after_point = 0U;
   static unsigned long long constexpr value = 
      (static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0')) * multiplier + get_int<C...>::value;
};

template <char Cf>
   requires is_digit<Cf>
struct get_int<Cf>{
   static unsigned constexpr multiplier = 1U;
 //  static constexpr unsigned int num_digits_after_point = 0U;
   static unsigned int constexpr value = static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0');
};

template<>
struct get_number<'.'>{
   static long double constexpr value = 0.0;
   static constexpr unsigned int num_digits_after_point = 0U;
   static constexpr unsigned int multiplier = 1U;
   static constexpr number_style style = number_style::Float;
};

template<char C>
  requires is_digit<C>
struct get_number<C>{
   static constexpr auto value = get_int<C>::value;
   static constexpr unsigned int multiplier = 1U;
   static constexpr unsigned int num_digits_after_point = 0U;
   static constexpr number_style style = number_style::Int;
};

long double constexpr shiftpoint( long double v){
   return v >= 1.0 ? shiftpoint(v / 10) : v;
};

template<char ...C>
struct get_number<'.',C...>{
   static long double constexpr value = 
      shiftpoint( static_cast<long double>(get_int<C...>::value));
   static constexpr unsigned int num_digits_after_point = sizeof...(C);
   static constexpr unsigned int multiplier = 1U;
   static constexpr number_style style = number_style::Float;
};

template<char Cf,char... C>
   requires is_digit<Cf> && (get_number<C...>::style == number_style::Float)
struct get_number<Cf,C...>{
   static long double constexpr value = get_int<Cf>::value * 
        get_number<C...>::multiplier + get_number<C...>::value;
   static unsigned long long constexpr multiplier 
     = get_number<C...>::multiplier * 10;
   static constexpr unsigned int num_digits_after_point 
     = get_number<C...>::num_digits_after_point;
   static constexpr number_style style = number_style::Float;
};

template<char Cf,char... C>
   requires is_digit<Cf> && (get_number<C...>::style == number_style::Int)
struct get_number<Cf,C...>{
   static constexpr auto value = get_int<Cf,C...>::value;
   static constexpr unsigned int num_digits_after_point = 0U;
   static constexpr number_style style = number_style::Int;
};
/**
 * @todo make sure that precision is not truncated. 
 * That is quite tricky as floating point is ultimately binary not decimal format
 * To a first approximation, decide on basis of number of digits after decimal.
 * The exact values per type we can argue about. Also provides a way to force a type,
 * though the other way would just be to add a postfix
 * Ultimately the UDL is a convenience. If you need higher precison, you can always declare your literal
 * as my_quantity{1.234567890}. Generally UDLs are useful for init by 0 or 1 etc.
**/

template <typename T>
struct max_digits_after_point ;

template <>
struct max_digits_after_point<float> { static constexpr unsigned int value = 6U;};

template <>
struct max_digits_after_point<double> { static constexpr unsigned int value = 12U;};

template <char... V>
auto constexpr operator "" _my_type()
{
    auto constexpr value = get_number<V...>::value;
    auto constexpr num_digits_after_point = get_number<V...>::num_digits_after_point;
    // N.B. This could be done better from the point of view of precision
    // and deciding which floating point type to return, but at this point 
    // it is just a question of verifying that it works
    // and that you can return different types of floats from this function
    if constexpr (std::is_floating_point_v<decltype(value)>){
      if constexpr ( (num_digits_after_point <= max_digits_after_point<float>::value) && (value < std::numeric_limits<float>::max()) ){
         return my_type<float>{static_cast<float>(value)};
      }else if constexpr (  (num_digits_after_point <= max_digits_after_point<double>::value) && (  value < std::numeric_limits<double>::max())){
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
   std::cout << "UDT returned in smallest type that doesnt lose precision\n";
   auto x = 1_my_type;
   auto constexpr y = 20000_my_type;
   auto z = 65537_my_type;

   static_assert(std::is_same<decltype(x),my_type<int8_t> >::value,"");
   static_assert(std::is_same<decltype(y),my_type<int16_t> const >::value,"");
   static_assert(std::is_same<decltype(z),my_type<int32_t> >::value,"");

   z = x;  // OK
   z = y;  // Great!
   // x = z ;// N/A my_type<int32_t> --> N/A my_type<int8_t> 

   auto constexpr a = 120.345_my_type;
   static_assert(std::is_same<decltype(a),my_type<float> const>::value,"");

   auto  b = 6000.345_my_type;
   static_assert(std::is_same<decltype(b),my_type<float>>::value,"");

   b = x; // OK
   b = y; // OK
  // b = z; // N/A my_type<int32_t> --> my_type<float>

   my_type<double> c = b;

   c = x; // OK 
   c = y; // OK 
   c = z; // OK 
   //x = b; //N/A  my_type<float> --> my_type<int8_t> 

   auto a1 = operator""_my_type<'1','2','3'>();

   auto d = 51.842105956934176_my_type;
   static_assert(std::is_same<decltype(d),my_type<long double> >::value,"");

   auto e = 51.0000000_my_type; // force double
   static_assert(std::is_same<decltype(e),my_type<double> >::value,"");
}





