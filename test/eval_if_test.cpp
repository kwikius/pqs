

#include <quan_matters/test/test.hpp>


#include <type_traits>

#include <pqs/meta/eval_if.hpp>

using pqs::meta::eval_if;

namespace {

   template <int x> 
   struct my_fun {
      typedef my_fun type;
   };

}

void eval_if_test()
{

   typedef eval_if<
         std::false_type,
         my_fun<1>, 
         std::false_type ,
         my_fun<2>, 
         std::false_type,
         my_fun<3>,
         std::false_type,
         my_fun<4>,
         std::false_type ,
         my_fun<5>, 
         std::false_type,
         my_fun<6>,
         std::false_type,
         my_fun<7>,
         my_fun<8>   //<--
   >::type type1;

    QUAN_CHECK((std::is_same<type1,my_fun<8> >::value))

   //type::fun(); 

   typedef eval_if<std::true_type,my_fun<1>,my_fun<2> >::type type2;
   QUAN_CHECK((std::is_same<type2,my_fun<1> >::value))

   typedef eval_if<std::false_type,my_fun<1>,my_fun<2> >::type type3;
   QUAN_CHECK((std::is_same<type3,my_fun<2> >::value))

   typedef eval_if<
         std::true_type,
         my_fun<1>,   // <--
         std::false_type ,
         my_fun<2>, 
         std::false_type,
         my_fun<3>,
         std::false_type,
         my_fun<4>,
         std::false_type ,
         my_fun<5>, 
         std::false_type,
         my_fun<6>,
         std::false_type,
         my_fun<7>,
         my_fun<8>
   >::type type4;
    QUAN_CHECK((std::is_same<type4,my_fun<1> >::value))

   typedef eval_if<
         std::false_type,
         my_fun<1>, 
         std::true_type ,
         my_fun<2>, // <--
         std::false_type,
         my_fun<3>,
         std::false_type,
         my_fun<4>,
         std::false_type,
         my_fun<7>,
         my_fun<8>
   >::type type5;
    QUAN_CHECK((std::is_same<type5,my_fun<2> >::value))

   typedef eval_if<
         std::false_type,
         my_fun<1>, 
         std::false_type ,
         my_fun<2>, // <--
         std::false_type,
         my_fun<3>,
         std::false_type,
         my_fun<4>,
         std::true_type,
         my_fun<7>, // <--
         my_fun<8>
   >::type type6;
    QUAN_CHECK((std::is_same<type6,my_fun<7> >::value))

   typedef double* x_type;

   typedef eval_if<
       std::is_integral<x_type>
         ,my_fun<1>
       ,std::is_union<x_type>
         ,my_fun<2>
       ,std::is_pointer<x_type>
         ,my_fun<3>
       ,std::is_arithmetic<x_type>
         ,my_fun<4>
       ,std::is_function<x_type>
         ,my_fun<5>
         ,my_fun<6>
   >::type type7;

    QUAN_CHECK((std::is_same<type7,my_fun<3> >::value))
        
}