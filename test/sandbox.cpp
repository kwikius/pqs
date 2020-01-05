#include "test.hpp"

#include <pqs/bits/binary_op.hpp>

namespace {

   struct my_type{};  

   void binary_op_test()
   {
       QUAN_CHECK((pqs::is_valid_binary_op<my_type,pqs::plus,my_type>::value == false))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::plus,int>::type,int>::value))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::minus,int>::type,int>::value))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::times,int>::type,int>::value))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::divides,int>::type,int>::value))
//TODO
    //   QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::shift_left,int>::type,int>::value))
    //   QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::shift_right,int>::type,int>::value))
    //   QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::div,int>::type,int>::value))
     //  QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::modulus,int>::type,int>::value))
     //  QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::modulus,int>::type,int>::value))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::bit_or,int>::type,int>::value))
     //  QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::bit_xor,int>::type,int>::value))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::bit_and,int>::type,int>::value))
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
   binary_op_test();
}