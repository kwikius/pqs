

#include <pqs/bits/base_quantity_of.hpp>

namespace {

   struct my_length{};


   // my_length is not compile time totally ordered so this should fail
   void compile_fail()
   {
      struct my_base_quantity : pqs::base_quantity_of<my_length>{};
   }
}

int main()
{
}