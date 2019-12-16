
#include "test.hpp"

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace {

   struct my_length{};

#if 0
   // my_length is not compile time totally ordered so this should fail
   void compile_fail()
   {
       struct my_base_quantity : pqs::base_quantity_of<my_length>{};
   }
#endif
   struct derived_uuid1 : pqs::universally_unique_id<0,100>{};

   void uuid_test()
   {
       typedef pqs::universally_unique_id<0,100> uuidL1;

       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::meta::equal_to,uuidL1>::value) );
       QUAN_CHECK( (pqs::binary_op<derived_uuid1,pqs::meta::equal_to,uuidL1>::value) );
       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::meta::equal_to,derived_uuid1>::value) );

       typedef pqs::universally_unique_id<100> uuidR1;

       QUAN_CHECK( (pqs::binary_op<uuidL1,pqs::meta::equal_to,uuidR1>::value) );
       QUAN_CHECK( (pqs::binary_op<derived_uuid1,pqs::meta::equal_to,uuidR1>::value) );
       QUAN_CHECK( (pqs::binary_op<uuidR1,pqs::meta::equal_to,derived_uuid1>::value) );

       QUAN_CHECK( (pqs::binary_op<uuidR1,pqs::meta::equal_to,uuidL1>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidL1,pqs::meta::less,uuidR1>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidR1,pqs::meta::less,uuidL1>::value) );

       typedef pqs::universally_unique_id<0,0> uuidL2;
       typedef pqs::universally_unique_id<1> uuidR2;

       QUAN_CHECK( (pqs::binary_op<uuidL2,pqs::meta::less,uuidR2>::value) );
       QUAN_CHECK( (not pqs::binary_op<uuidR2,pqs::meta::less,uuidL2>::value) );
       QUAN_CHECK( (not pqs::binary_op<uuidR2,pqs::meta::equal_to,uuidL2>::value) );

       typedef pqs::universally_unique_id<1,2,3,4> uuidL3;
       typedef pqs::universally_unique_id<100> uuidR3;
       QUAN_CHECK( ( not pqs::binary_op<uuidL3,pqs::meta::equal_to,uuidR3>::value) );
       QUAN_CHECK( ( not pqs::binary_op<uuidR3,pqs::meta::less,uuidL3>::value) );
   }

   void base_quantity_concept_test()
   {
      typedef pqs::base_length base_length;

      QUAN_CHECK(( pqs::is_base_quantity<base_length>::value))

      QUAN_CHECK(( pqs::base_quantity_equal_to<base_length,base_length>::value))
      QUAN_CHECK(( pqs::base_quantity_less<base_length,base_length>::value == false))

   }
}

void base_quantity_test()
{
   base_quantity_concept_test();
   uuid_test();
}