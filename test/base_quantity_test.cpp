
#include "test.hpp"

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/types/base_quantity/length.hpp>
#include <pqs/types/base_quantity/time.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/meta/identity_function.hpp>

namespace {

   struct derived_uuid1 : pqs::uuid<0,100>{};

   void uuid_test()
   {
       using uuidL1 = pqs::uuid<0,100> ;

       static_assert(pqs::binary_op_v<uuidL1,pqs::equal_to,uuidL1>);
       static_assert(pqs::binary_op_v<derived_uuid1,pqs::equal_to,uuidL1>);
       static_assert(pqs::binary_op_v<uuidL1,pqs::equal_to,derived_uuid1>);

       using uuidR1 = pqs::uuid<100> ;

       static_assert(pqs::binary_op_v<uuidL1,pqs::equal_to,uuidR1>);
       static_assert(pqs::binary_op_v<derived_uuid1,pqs::equal_to,uuidR1>);
       static_assert(pqs::binary_op_v<uuidR1,pqs::equal_to,derived_uuid1>);

       static_assert(pqs::binary_op_v<uuidR1,pqs::equal_to,uuidL1>);
       static_assert( not pqs::binary_op_v<uuidL1,pqs::less,uuidR1>);
       static_assert( not pqs::binary_op_v<uuidR1,pqs::less,uuidL1>);

       using uuidL2 = pqs::uuid<0,0> ;
       using uuidR2 = pqs::uuid<1> ;

       static_assert(pqs::binary_op_v<uuidL2,pqs::less,uuidR2>);
       static_assert(not pqs::binary_op_v<uuidR2,pqs::less,uuidL2>);
       static_assert(not pqs::binary_op_v<uuidR2,pqs::equal_to,uuidL2>);

       using uuidL3 = pqs::uuid<1,2,3,4> ;
       using uuidR3 = pqs::uuid<100> ;

       static_assert( not pqs::binary_op_v<uuidL3,pqs::equal_to,uuidR3>);
       static_assert( not pqs::binary_op_v<uuidR3,pqs::less,uuidL3>);
   }

   void base_quantity_concept_test()
   {
      typedef pqs::base_length base_length;

      static_assert(pqs::is_base_quantity<base_length>);
      static_assert(pqs::meta::is_identity_function<base_length>::value);

      static_assert(pqs::binary_op_v<base_length,pqs::equal_to, base_length>);
      static_assert(pqs::binary_op_v<base_length,pqs::less,base_length> == false);

      typedef pqs::base_time base_time;

      static_assert(pqs::meta::is_identity_function<base_time>::value);

      static_assert( not pqs::binary_op_v<base_length,pqs::equal_to, base_time>);
      static_assert( pqs::binary_op_v<base_length,pqs::less,base_time>);
      static_assert( not pqs::binary_op_v<base_time,pqs::less,base_length>);

   }
}

void base_quantity_test()
{
   base_quantity_concept_test();
   uuid_test();
}