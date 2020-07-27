

#include <pqs/concepts/associated/dimensionally_equivalent.hpp>

int main()
{
   // dimensionally equivalent is false for ints
   static_assert ( pqs::dimensionally_equivalent<int,int> ); 
}