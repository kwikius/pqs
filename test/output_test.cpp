
#include <pqs/bits/dimension_to_fixed_string.hpp>
#include <pqs/si/speed.hpp>
#include <pqs/si/length.hpp>
#include <pqs/imperial/length.hpp>

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
   auto constexpr x = pqs::dimension_to_fixed_string<Qbe,ms,charset>();
   std::cout << x <<'\n';

   // dimension_list
   using D = decltype(pqs::abstract_time<3> * pqs::abstract_length<-3> * pqs::abstract_current<-1>);
   std::cout << pqs::dimension_to_fixed_string<D,ms,pqs::charset_utf8>() << '\n';
   std::cout << pqs::dimension_to_fixed_string<D,ms,pqs::charset_ascii>() << '\n';
   // custom dimension
   struct cd : decltype(pqs::abstract_length<> / pqs::pow<2>(pqs::abstract_time<>) ){};
   std::cout << pqs::dimension_to_fixed_string<cd,ms,pqs::charset_utf8>() << '\n';
   std::cout << pqs::dimension_to_fixed_string<cd,ms,pqs::charset_ascii>() << '\n';

   using Q = pqs::si::speed::m_per_s<>;
   std::cout <<  pqs::dimension_to_fixed_string<Q, pqs::charset_utf8>()  << '\n';
   std::cout <<  pqs::dimension_to_fixed_string<Q, pqs::charset_ascii>()  << '\n';

   using L = pqs::si::length::ft<>;
   std::cout <<  pqs::dimension_to_fixed_string<L, pqs::charset_utf8>()  << '\n';
   std::cout <<  pqs::dimension_to_fixed_string<L, pqs::charset_ascii>()  << '\n';

   using L1 = pqs::imperial::length::ft<>;
   std::cout <<  pqs::dimension_to_fixed_string<L1, pqs::charset_utf8>()  << '\n';
   std::cout <<  pqs::dimension_to_fixed_string<L1, pqs::charset_ascii>()  << '\n';
}
