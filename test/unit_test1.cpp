
#include "test.hpp"
#include <pqs/si/length.hpp>

using namespace pqs;

namespace {

   void unit_concept_test()
   {
      using U = si::proper_unit< 
         decltype( abstract_length<> * abstract_time<2> ),
         exponent10<1>
      >;

      static_assert( unit<U> );
      static_assert( si::is_normative_unit<U> );

      using D = get_dimension<U>;
      static_assert( dimension< D > );

      using Ds = get_simple_dimension< U > ;
      static_assert( dimension< Ds > );

      using Sm = get_measurement_system<U>;
      static_assert( measurement_system<Sm > );

      using Cf = get_conversion_factor< U >;
      static_assert( is_conversion_factor<Cf> );
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void unit_test()
#endif
{
   unit_concept_test();
}
