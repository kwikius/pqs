

#include "test.hpp"

void quantity_syntax_test();
void base_quantity_exp_test();

void base_quantity_test();
void dimension_test();
void dimension_test1();
void dimension_test2();
void conversion_factor_test1();

void type_list_test();
void eval_if_test();
void meta_to_power_test();

void make_quantity_test();

void conversion_factor_test2();
void basic_concepts_test();

void experimental_test();
void scaled_value_test();
void binary_op_test();
void sandbox();


int  errors = 0;

int main()
{
   std::cout << "pqs test\n";
   quantity_syntax_test();
  // base_dimension_ratio_test();
   dimension_test();
   dimension_test1();
   dimension_test2();

   base_quantity_exp_test();
   conversion_factor_test1();
   type_list_test();
   eval_if_test();
   meta_to_power_test();
   conversion_factor_test2();
  // make_quantity_test();
   basic_concepts_test();
   base_quantity_test();
   experimental_test();
   scaled_value_test();
   binary_op_test();

   sandbox();

   EPILOGUE
}