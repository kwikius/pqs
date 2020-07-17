#include "test.hpp"

#include <pqs/concepts/associated/binary_op.hpp>

namespace {

 struct my_type{};  

   void binary_op_test1()
   {
      QUAN_CHECK((pqs::is_valid_binary_op<my_type,pqs::plus,my_type>::value == false))
   }

   void binary_op_bool_test()
   {
      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::plus,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::plus,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::minus,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::minus,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::times,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::times,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::divides,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::divides,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::bit_or,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::bit_or,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::bit_and,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::bit_and,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::logical_or,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::logical_or,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::logical_and,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::logical_and,bool>::type,bool>::value))

      QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::logical_and,bool>::value == true))
      QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::logical_and,bool>::type,bool>::value))
   }
   
   void binary_op_int_int_test()
   {
       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::plus,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::plus,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::minus,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::minus,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::times,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::times,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::divides,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::divides,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::bit_or,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::bit_or,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::bit_and,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::bit_and,int>::type,int>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::logical_or,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::logical_or,int>::type,bool>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::logical_and,int>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::logical_and,int>::type,bool>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::logical_and,bool>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::logical_and,bool>::type,bool>::value))
   }

   void binary_op_int_double_test()
   {

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::plus,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::plus,double>::type,double>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::minus,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::minus,double>::type,double>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::times,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::times,double>::type,double>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::divides,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::divides,double>::type,double>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::logical_or,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::logical_or,double>::type,bool>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<int,pqs::logical_and,double>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<int, pqs::logical_and,double>::type,bool>::value))

       QUAN_CHECK((pqs::is_valid_binary_op<bool,pqs::logical_and,bool>::value == true))
       QUAN_CHECK((std::is_same<pqs::binary_op<bool, pqs::logical_and,bool>::type,bool>::value))
   }

   // TODO more tests on inbuilt types

}

void binary_op_test()
{
   binary_op_test1();
   binary_op_bool_test();
   binary_op_int_int_test();
   binary_op_int_double_test();
}