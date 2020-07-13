
#include <cstdlib>
#include "../test.hpp"

#include <iostream>
#include <string>

namespace {
   
   struct compile_info_t{
      std::string compiler;
      std::string flags;
      std::string includes;
      std::string log_file;
   };
}

//bool compile_fail_test(std::string const & filename, std::string const & cmd_head_in = cmd_head, std::string const & log_file_in = log_file)
bool compile_fail_test(std::string const & filename, compile_info_t const & compile_info)
{
   std::string header = "echo '#### compile fail test on " + filename + " ####\n'";//  >> " + compile_info.log_file;
   system(header.c_str());
   std::string cmd_head = compile_info.compiler + " " + compile_info.flags + " " + compile_info.includes;
   std::string cmd = cmd_head + " " + filename + " >> " + compile_info.log_file + " 2>&1" ;
   int result = system(cmd.c_str());
   if ( result == 0){
      std::string tail =  "echo '#### UNEXPECTED : compilation of " + filename + " succeeded: TEST FAILED \n'";//  >> " + compile_info.log_file;
      system (tail.c_str());
   }else{
      std::string tail =  "echo 'TEST SUCCESSFUL : ( compilation of " + filename + " failed as expected)\n'";// >> " + compile_info.log_file;
      system (tail.c_str());
   }
   return result != 0;
}

int main()
{
   compile_info_t compile_info;
#if 0
   compile_info.compiler   = "g++-7";
   compile_info.flags      = "-std=c++11 -fmax-errors=1";
#else
    compile_info.compiler   = "g++-9";
    compile_info.flags      = "-std=c++2a -fconcepts -fmax-errors=1";
#endif
   compile_info.includes   = "-I../../src/include";
   compile_info.log_file   = "compile_fail_log.txt";
   
   std::string header = "echo '########## starting compile fail test suite ##########\n'" ;//  > " + compile_info.log_file;
   system (header.c_str());

   QUAN_CHECK( compile_fail_test("base_quantity_totally_ordered_test.cpp",compile_info) )
   QUAN_CHECK( compile_fail_test("scaled_value_narrowing_conversion_test.cpp",compile_info) )
   QUAN_CHECK( compile_fail_test("add_quantity_in_different_unit_system_test.cpp",compile_info) )
   QUAN_CHECK( compile_fail_test("add_quantities_not_dimensionally_equivalent.cpp",compile_info) )
   QUAN_CHECK( compile_fail_test("implicit_cast_quantity.cpp",compile_info) )

   std::string tail =  "echo '########## compile fail tests completed ##########\n'";// >> " + compile_info.log_file;
   system (tail.c_str());

   EPILOGUE
}

int errors = 0;


