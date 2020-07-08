
//#include <pqs/concepts/dimension.hpp>
//#include <pqs/bits/base_quantities.hpp>
//#include <pqs/si/unit.hpp>
//
//#include <pqs/si/quantity/plus.hpp>
//#include <pqs/si/measurement_system_def.hpp>
//#include <pqs/instance/basic_quantity_fwd.hpp>
//#include <pqs/si/unit.hpp>

#include <pqs/si/length.hpp>

using namespace pqs;

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
  using u = pqs::si::proper_unit< 
      decltype( abstract_length<> * abstract_time<2> ),
      pqs::exponent10<1>
  >;

 static_assert ( pqs::unit<u> ,"");

 static_assert (pqs::si::is_proper_si_unit<u> );

 auto res = pqs::si::length::m<>{1} * pqs::si::length::ft<>{1};

}
