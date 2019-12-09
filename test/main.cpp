

#include <quan_matters/test/test.hpp>

void quantity_syntax_test1();
void base_dimension_ratio_test();
void dimension_test();
void ratio_exp_test();
void type_list_test();
void eval_if_test();

int errors = 0;

int main()
{
   quantity_syntax_test1();
   base_dimension_ratio_test();
   dimension_test();
   ratio_exp_test();
   type_list_test();
   eval_if_test();

   QUAN_EPILOGUE
}