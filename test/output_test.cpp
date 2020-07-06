
#include <pqs/bits/dimension_as_fixed_string.hpp>
#include "test.hpp"

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else
void output_test()
#endif
{
   using Qbe = pqs::exp_mass<-1,2>;
   using ms = pqs::si_measurement_system;
 #if 1
   using charset = pqs::charset_utf8;
 #else
   using charset = pqs::charset_ascii;
 #endif

   // base_dimension_exponent
   auto constexpr x = pqs::dimension_as_fixed_string<charset,ms,Qbe>;
   std::cout << x <<'\n';

   // dimension_list
   using D = decltype(pqs::abstract_time<3> * pqs::abstract_length<-3> * pqs::abstract_current<-1>);
   std::cout << pqs::dimension_as_fixed_string<charset,ms,D> << '\n';

   // custom dimension
   struct cd : decltype(pqs::abstract_length<> / pqs::pow<2>(pqs::abstract_time<>) ){};
   std::cout << pqs::dimension_as_fixed_string<charset,ms,cd> << '\n';
}
