
#include <quan_matters/test/test.hpp>

#include <pqs/bits/ratio_exp.hpp>

namespace {

   void is_ratio_exp_test()
   {
      typedef pqs::ratio_exp<
         std::ratio<1,2>,1
      > ratio_exp;

      typedef pqs::ratio_exp<
         int,1
      > ratio_exp1;

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp>::value));

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp1>::value == false));
   }

   void ratio_exp_lt_10_test()
   {
      typedef  pqs::ratio_exp<
         std::ratio<210000,2>
         ,1
      > ratio_exp2;

      typedef  typename pqs::detail::ratio_exp_make_ratio_less_than_10<
         ratio_exp2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::ratio_exp<std::ratio<21,20>, 6 > >::value ))

      typedef  pqs::ratio_exp<
         std::ratio<-210000,2>
         ,1
      > ratio_exp3;
         typedef  typename pqs::detail::ratio_exp_make_ratio_less_than_10<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::ratio_exp<std::ratio<-21,20>, 6 > >::value ))

   }

   void ratio_exp_gte_1_test()
   {

     typedef  pqs::ratio_exp<
         std::ratio<21,20000>
         ,6
      > ratio_exp2;

      typedef  typename pqs::detail::ratio_exp_make_ratio_greater_equal_1<
            ratio_exp2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::ratio_exp<std::ratio<21,20>, 3> >::value ))

      typedef  pqs::ratio_exp<
         std::ratio<-21,20000>
         ,6
      > ratio_exp3;

      typedef  typename pqs::detail::ratio_exp_make_ratio_greater_equal_1<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::ratio_exp<std::ratio<-21,20>, 3 > >::value ))

   }

   // intmax_t is 9223372036854775807 on my system
   //             9223372036854775807
   // e.g approx 10^19
   // assume a max of 6 decimals for the fraction, so either part of the rational can be between 0 and 10^6
   // then either part of rational can be muxed by 10^12
   // so therefore one can work a range of exponents of 10^12
   // e.g 1 km + 1 n.m. After that there may be issues
   void ratio_add_exp_test()
   {
      typedef pqs::ratio_exp<std::ratio<1,2>,3> t1;
       
      using pqs::detail::ratio_exp_add_exp_n;

      typedef ratio_exp_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::ratio_exp<std::ratio<1,20000>,7> >::value ))

      typedef ratio_exp_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))

      typedef ratio_exp_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::ratio_exp<std::ratio<1,20000>,7> >::value ))

      typedef ratio_exp_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))
   }

  /*
       to add ratio_exp.
       First normalise
  */
   void ratio_exp_normalise_test()
   {
       typedef pqs::ratio_exp<std::ratio<1,200>,4> t1;
       typedef pqs::ratio_exp_normalise<t1>::type t2;

       QUAN_CHECK((std::is_same<t2,pqs::ratio_exp<std::ratio<5,1>,1> >::value ))

     //  int x = t2{};

       typedef pqs::ratio_exp<std::ratio<201,20>,-3> t3;
       typedef pqs::ratio_exp_normalise<t3>::type t4;

       QUAN_CHECK((std::is_same<t4,pqs::ratio_exp<std::ratio<201,200>,-2> >::value ))

       typedef pqs::ratio_exp<std::ratio<202000,20>,-9> t5;
       typedef pqs::ratio_exp_normalise<t5>::type t6;

       QUAN_CHECK((std::is_same<t6,pqs::ratio_exp<std::ratio<101,100>,-5> >::value ))

       typedef pqs::ratio_exp<std::ratio<9,1>,4> t7;
       typedef pqs::ratio_exp_normalise<t7>::type t8;

       QUAN_CHECK((std::is_same<t7,t8 >::value ))

       typedef pqs::ratio_exp<std::ratio<1>,4> t9;
       typedef pqs::ratio_exp_normalise<t9>::type t10;
       QUAN_CHECK((std::is_same<t9,t10 >::value ))

       typedef pqs::ratio_exp<std::ratio<1,10>,4> t11;
       typedef pqs::ratio_exp_normalise<t11>::type t12;

     // int x = t12{};
       QUAN_CHECK((std::is_same<t12,pqs::ratio_exp<std::ratio<1,1>,3 > >::value ))
   }
  
} // namespace

void ratio_exp_test1()
{
    is_ratio_exp_test();
    ratio_exp_lt_10_test();
    ratio_exp_gte_1_test();
    ratio_add_exp_test();
    ratio_exp_normalise_test();
}