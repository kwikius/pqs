
#include <quan_matters/test/test.hpp>

#include <pqs/meta/ratio_exp.hpp>

namespace {

   void is_ratio_exp_test()
   {
      typedef pqs::meta::ratio_exp<
         std::ratio<1,2>,1
      > ratio_exp;

      typedef pqs::meta::ratio_exp<
         int,1
      > ratio_exp1;

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp>::value));

      QUAN_CHECK((pqs::meta::is_ratio_exp<ratio_exp1>::value == true));
   }

   void ratio_exp_lt_10_test()
   {
      typedef  pqs::meta::ratio_exp<
         std::ratio<210000,2>
         ,1
      > ratio_exp2;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_less_than_10<
            ratio_exp2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::meta::ratio_exp<std::ratio<21,20>, 6 > >::value ))

      typedef  pqs::meta::ratio_exp<
         std::ratio<-210000,2>
         ,1
      > ratio_exp3;
         typedef  typename pqs::meta::detail::ratio_exp_make_ratio_less_than_10<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::meta::ratio_exp<std::ratio<-21,20>, 6 > >::value ))

   }

   void ratio_exp_gt_0_pt_1_test()
   {

   // ratio_exp_abs_make_ratio_greater_than_0_pt_1

     typedef  pqs::meta::ratio_exp<
         std::ratio<21,20000>
         ,6
      > ratio_exp2;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_greater_than_0_pt_1<
            ratio_exp2
      >::type result_type;

     // int x = result_type{};

      QUAN_CHECK( (std::is_same<result_type,pqs::meta::ratio_exp<std::ratio<21,200>, 4 > >::value ))

      typedef  pqs::meta::ratio_exp<
         std::ratio<-21,20000>
         ,6
      > ratio_exp3;

      typedef  typename pqs::meta::detail::ratio_exp_make_ratio_greater_than_0_pt_1<
            ratio_exp3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::meta::ratio_exp<std::ratio<-21,200>, 4 > >::value ))

   }

   void ratio_add_exp_test()
   {
      QUAN_CHECK( (pqs::meta::detail::to_power<10,0>::value == 1));

      QUAN_CHECK( (pqs::meta::detail::to_power<10,1>::value == 10));
      QUAN_CHECK( (pqs::meta::detail::to_power<10,2>::value == 100));
/*
      typedef pqs::meta::ratio_exp<std::ratio<1,2>,3> t1;
       
      using pqs::meta::detail::ratio_exp_add_exp_n;

      typedef ratio_exp_add_exp_n<t1,2>::type t2;

      int n = t2{};

      QUAN_CHECK( (t2::exp == 5))
      QUAN_CHECK((std::is_same<t2::ratio,std::ratio<1,200> >::value ))
*/
   }

} // namespace

void ratio_exp_test()
{
    is_ratio_exp_test();
    ratio_exp_lt_10_test();
    ratio_exp_gt_0_pt_1_test();
    ratio_add_exp_test();
}