#include "test.hpp"

#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>

using namespace pqs;

namespace{

#if (defined(__cpp_nontype_template_args)) && (__cplusplus > 201703L)
   template <auto D>
   struct test_list { static constexpr auto value = D;};
#endif

#if defined __cpp_decltype_auto
   auto constexpr fun()
   {
#if (defined(__cpp_nontype_template_args)) && (__cplusplus > 201703L)
      return test_list< exp_length_v<1> / ( exp_time_v<1> * exp_time_v<1> ) >::value;
#else
      return  exp_length_v<1> / ( exp_time_v<1> * exp_time_v<1>);
#endif

   }

#endif
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{

#if defined __cpp_decltype_auto
  // get type in erro message
auto x =fun();
#endif
#if defined PQS_STANDALONE
   EPILOGUE
#endif

}