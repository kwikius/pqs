
#include "test.hpp"

#include <pqs/type_templates/conversion_factor.hpp>

namespace {

   void is_conversion_factor_test()
   {

      typedef pqs::conversion_factor<
         std::ratio<1,2>,std::ratio<1>
      > conversion_factor;

      typedef pqs::conversion_factor<
         int,int
      > conversion_factor1;

      QUAN_CHECK((pqs::is_conversion_factor<conversion_factor>::value));

      QUAN_CHECK((pqs::is_conversion_factor<conversion_factor1>::value == false));
   }

   void conversion_factor_lt_10_test()
   {
      typedef  pqs::conversion_factor<
         std::ratio<210000,2>,
         std::ratio<1>
      > conversion_factor2;

      typedef  typename pqs::detail::conversion_factor_make_ratio_less_than_10<
         conversion_factor2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::conversion_factor<std::ratio<21,20>, std::ratio<6> > >::value ))

      typedef  pqs::conversion_factor<
         std::ratio<-210000,2>,
         std::ratio<1>
      > conversion_factor3;
         typedef  typename pqs::detail::conversion_factor_make_ratio_less_than_10<
            conversion_factor3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::conversion_factor<std::ratio<-21,20>,std::ratio<6> > >::value ))

     typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > one;

     typedef  typename pqs::detail::conversion_factor_make_ratio_less_than_10<
          one
      >::type one_result_type;
      QUAN_CHECK( (std::is_same<one_result_type,one>::value ))

   }

   void conversion_factor_gte_1_test()
   {

     typedef  pqs::conversion_factor<
         std::ratio<21,20000>,
         std::ratio<6>
      > conversion_factor2;

      typedef  typename pqs::detail::conversion_factor_make_ratio_greater_equal_1<
            conversion_factor2
      >::type result_type;

      QUAN_CHECK( (std::is_same<result_type,pqs::conversion_factor<std::ratio<21,20>, std::ratio<3> > >::value ))

      typedef  pqs::conversion_factor<
         std::ratio<-21,20000>,
         std::ratio<6>
      > conversion_factor3;

      typedef  typename pqs::detail::conversion_factor_make_ratio_greater_equal_1<
            conversion_factor3
      >::type result_type1;

      QUAN_CHECK( (std::is_same<result_type1,pqs::conversion_factor<std::ratio<-21,20>,std::ratio<3> > >::value ))

     typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > one;

     typedef  typename pqs::detail::conversion_factor_make_ratio_greater_equal_1<
          one
      >::type one_result_type;
      QUAN_CHECK( (std::is_same<one_result_type,one>::value ))

     

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
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<3> > t1;
       
      using pqs::detail::conversion_factor_add_exp_n;

      typedef conversion_factor_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::conversion_factor<std::ratio<1,20000>,std::ratio<7> > >::value ))

      typedef conversion_factor_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))

      typedef conversion_factor_add_exp_n<t1,4>::type t2;

      QUAN_CHECK((std::is_same<t2,pqs::conversion_factor<std::ratio<1,20000>,std::ratio<7> > >::value ))

      typedef conversion_factor_add_exp_n<t2,-4>::type t3;

      QUAN_CHECK((std::is_same<t3,t1>::value ))
   }

  /*
       to add conversion_factor.
       First normalise
  */
   void conversion_factor_normalise_test()
   {
       typedef pqs::conversion_factor<std::ratio<1,200>,std::ratio<4> > t1;
       typedef pqs::detail::conversion_factor_normalise<t1>::type t2;

       QUAN_CHECK((std::is_same<t2,pqs::conversion_factor<std::ratio<5,1>,std::ratio<1> > >::value ))

     //  int x = t2{};

       typedef pqs::conversion_factor<std::ratio<201,20>,std::ratio<-3> > t3;
       typedef pqs::detail::conversion_factor_normalise<t3>::type t4;

       QUAN_CHECK((std::is_same<t4,pqs::conversion_factor<std::ratio<201,200>,std::ratio<-2> > >::value ))

       typedef pqs::conversion_factor<std::ratio<202000,20>,std::ratio<-9> > t5;
       typedef pqs::detail::conversion_factor_normalise<t5>::type t6;

       QUAN_CHECK((std::is_same<t6,pqs::conversion_factor<std::ratio<101,100>,std::ratio<-5> > >::value ))

       typedef pqs::conversion_factor<std::ratio<9,1>,std::ratio<4> > t7;
       typedef pqs::detail::conversion_factor_normalise<t7>::type t8;

       QUAN_CHECK((std::is_same<t7,t8 >::value ))

       typedef pqs::conversion_factor<std::ratio<1>,std::ratio<4> > t9;
       typedef pqs::detail::conversion_factor_normalise<t9>::type t10;
       QUAN_CHECK((std::is_same<t9,t10 >::value ))

       typedef pqs::conversion_factor<std::ratio<1,10>,std::ratio<4> > t11;
       typedef pqs::detail::conversion_factor_normalise<t11>::type t12;

     // int x = t12{};
       QUAN_CHECK((std::is_same<t12,pqs::conversion_factor<std::ratio<1,1>,std::ratio<3> > >::value ))
   }
  
} // namespace

void conversion_factor_test1()
{
    is_conversion_factor_test();
    conversion_factor_lt_10_test();
    conversion_factor_gte_1_test();
    ratio_add_exp_test();
    conversion_factor_normalise_test();
}