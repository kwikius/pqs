

#include <quan_matters/test/test.hpp>

void quantity_syntax_test1();
void base_dimension_ratio_test();

int errors = 0;

int main()
{
    quantity_syntax_test1();
    base_dimension_ratio_test();

   QUAN_EPILOGUE
}