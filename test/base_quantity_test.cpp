
#include "test.hpp"

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/meta/identity_function.hpp>

namespace {

   struct derived_uuid1 : pqs::universally_unique_id<0,100>{};

   void uuid_test()
   {
       typedef pqs::universally_unique_id<0,100> uuidL1;

       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::equal_to,uuidL1>::value) );
       QUAN_CHECK( (pqs::binary_op<derived_uuid1,pqs::equal_to,uuidL1>::value) );
       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::equal_to,derived_uuid1>::value) );

       typedef pqs::universally_unique_id<100> uuidR1;

       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::equal_to,uuidR1>::value) );
       QUAN_CHECK( (pqs::binary_op<derived_uuid1,pqs::equal_to,uuidR1>::value) );
       QUAN_CHECK( (pqs::binary_op<uuidR1,pqs::equal_to,derived_uuid1>::value) );

       QUAN_CHECK( (pqs::binary_op<uuidR1,pqs::equal_to,uuidL1>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidL1,pqs::less,uuidR1>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidR1,pqs::less,uuidL1>::value) );

       typedef pqs::universally_unique_id<0,0> uuidL2;
       typedef pqs::universally_unique_id<1> uuidR2;

       QUAN_CHECK( (pqs::binary_op<uuidL2,pqs::less,uuidR2>::value) );
       QUAN_CHECK( (not pqs::binary_op<uuidR2,pqs::less,uuidL2>::value) );
       QUAN_CHECK( (not pqs::binary_op<uuidR2,pqs::equal_to,uuidL2>::value) );

       typedef pqs::universally_unique_id<1,2,3,4> uuidL3;
       typedef pqs::universally_unique_id<100> uuidR3;
       QUAN_CHECK( ( not pqs::binary_op<uuidL3,pqs::equal_to,uuidR3>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidR3,pqs::less,uuidL3>::value) );
   }

   void base_quantity_concept_test()
   {
      typedef pqs::base_length base_length;

      QUAN_CHECK(( pqs::is_base_quantity_legacy<base_length>::value))
      QUAN_CHECK(( pqs::meta::is_identity_function<base_length>::value))

      QUAN_CHECK(( pqs::binary_op<base_length,pqs::equal_to, base_length>::value))
      QUAN_CHECK(( pqs::binary_op<base_length,pqs::less,base_length>::value == false))

      typedef pqs::base_time base_time;

      QUAN_CHECK(( pqs::meta::is_identity_function<base_time>::value))

      QUAN_CHECK(( not pqs::binary_op<base_length,pqs::equal_to, base_time>::value))
      QUAN_CHECK(( pqs::binary_op<base_length,pqs::less,base_time>::value))
      QUAN_CHECK(( not pqs::binary_op<base_time,pqs::less,base_length>::value))

   }
}

void base_quantity_test()
{
   base_quantity_concept_test();
   uuid_test();
}