
#include <iostream>
#include <chrono>
#include <pqs/systems/si/time.hpp>

namespace pqs::si{

   template <char... C>
   inline constexpr auto operator ""ns() -> auto
   { 
      //N.B ##### simple return type for exposition only ####
      return si::time::ns<int>{1}; 
   }
}

int main()
{

#if 1

   pqs::si::time::s<> a;
   auto b = pqs::si::operator""ns<'5','.','3'>(); // [1]
   auto c = pqs::si::time::ns<>(5.3); // alternative syntax (gcc9)
   auto d = a + b;

   std::chrono::nanoseconds x;
   auto y = std::literals::operator""ns(5.3); // [2]
   auto z = x + y;

#else

   pqs::si::time::s a;
   auto b = pqs::si::5.3ns; // error n/a
   auto c = a + b;

   std::chrono::nanoseconds x;
   auto y = std::literals::5.3ns; // error n/a
   auto z = x + y;

#endif
}
/*
[1]
   The variadic option is reuired AFAIK to choose the value_type of the result ( for floats also)  at compiletime
   see https://github.com/kwikius/pqs/blob/master/examples/bespoke_user_defined_literal.cpp
[2]
   std::chrono always chooses long double which is inconvenient for a microcontroller for example
   where the natural system type is float (e.g ARM cortex M4 https://www.arm.com/products/silicon-ip-cpu/cortex-m/cortex-m4)
*/