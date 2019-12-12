

#include "test.hpp"

void quantity_syntax_test1();
void base_dimension_ratio_test();
void dimension_test();
void conversion_factor_test1();

void type_list_test();
void eval_if_test();
void meta_to_power_test();

void make_quantity_test();

void conversion_factor_test2();

int errors = 0;

int main()
{
   quantity_syntax_test1();
   base_dimension_ratio_test();
   dimension_test();
   conversion_factor_test1();
   type_list_test();
   eval_if_test();
   meta_to_power_test();
   conversion_factor_test2();
   make_quantity_test();

   EPILOGUE
}