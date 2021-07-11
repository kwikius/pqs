
/*
  UDL function that returns the type with smallest footprint
  so for example
  127_my_type would return an underlying type of signed char etc

*/

#include <pqs/bits/meta/literal_value.hpp>

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

template <char... V>
auto constexpr operator "" _my_type()
{
   return my_type{pqs::meta::literal_value<V...>()};
}

//#################################################
#include <iostream>
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
   z = y;  // OK!
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





