

#include <pqs/concepts/associated/dimensionally_equivalent.hpp>

int main()
{
   // dimensionally equivaelent is undefined except for ints
   bool constexpr x = pqs::dimensionally_equivalent<int,int>;
}