
#include "test.hpp"

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/base_quantities/physical/length.hpp>

namespace {

   void base_quantity_concept_test()
   {
      typedef pqs::physical::base_quantity_length base_length;

      QUAN_CHECK(( pqs::is_base_quantity<base_length>::value))

      QUAN_CHECK(( pqs::base_quantity_equal_to<base_length,base_length>::value))
      QUAN_CHECK(( pqs::base_quantity_less<base_length,base_length>::value == false))

   }
}

void base_quantity_test()
{
   base_quantity_concept_test();
}