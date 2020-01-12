#include "test.hpp"

#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>

namespace{
   void fun()
   {
      using pqs_exposition::exp;
      using pqs::base_length;
      using pqs::times;
      using pqs::binary_op;

      QUAN_CHECK((not pqs::is_base_quantity_exp<int>::value))

      typedef exp<base_length,2> tl;
      typedef exp<base_length,3> tr;

      typedef pqs::get_base_quantity<tl>::type lhsb;
      typedef pqs::get_base_quantity<tr>::type rhsb;

      static_assert(pqs::is_base_quantity<lhsb>::value,"");
      static_assert(pqs::is_base_quantity<rhsb>::value,"");

      typedef pqs::get_base_quantity_id<lhsb>::type lhsid;

      typedef pqs::get_base_quantity_id<rhsb>::type rhsid;


      typedef pqs::make_base_quantity_exp<lhsid,pqs::get_exponent<tl>::type>::type b;


      //   int x = lhsid{};
    // int x = pqs::newtonian_universe::length_uuid{};

      typedef binary_op<tl,times,tr>::type result_type;

   //   int x = result_type{};
      
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{

fun();
#if defined PQS_STANDALONE
   EPILOGUE
#endif

}