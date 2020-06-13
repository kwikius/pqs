#include "test.hpp"

#include <pqs/bits/base_quantities.hpp>

#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>

using namespace pqs;

namespace{

  
   template <auto D>
   struct test_list { static constexpr auto value = D;};

   auto constexpr fun()
   {
      return test_list< exp_length_v<1> / ( exp_time_v<1> * exp_time_v<1> ) >::value;
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{

  // get type in erro message
 int x =fun();
#if defined PQS_STANDALONE
   EPILOGUE
#endif

}