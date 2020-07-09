
#include "test.hpp"

void quantity_syntax_test();
void base_quantity_exp_test();
void base_quantity_test();
void dimension_test();
void dimension_test1();
void dimension_test2();
void dimension_test3();
void type_list_test();
void eval_if_test();
void meta_to_power_test();
void make_quantity_test();
void conversion_factor_test1();
void conversion_factor_test2();
void conversion_factor_test3();
void basic_concepts_test();
void experimental_test();
void scaled_value_test();
void binary_op_test();
void sandbox();
void output_test();
void basic_quantity_test();
void unit_test();

int errors = 0;

int main()
{
   std::cout << "pqs test\n";

   basic_concepts_test();

   type_list_test();
   eval_if_test();
   meta_to_power_test();
   binary_op_test();
   base_quantity_test();

   conversion_factor_test1();
   conversion_factor_test2();
   conversion_factor_test3();

   base_quantity_exp_test();

   dimension_test();
   dimension_test1();
   dimension_test2();
   dimension_test3();

   output_test();

   unit_test();

   scaled_value_test();

   basic_quantity_test();
   quantity_syntax_test();
 
   experimental_test();

   sandbox();

   EPILOGUE
}