

#include <quan_matters/test/test.hpp>

#include <pqs/bits/ratio_exp.hpp>

#include <iostream>

namespace pqs {

   // return 1 if  lhs > rhs
   // return 0 if Lhs == Rhs,
   // return -1 if lhs < rhs

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_compare{
      typedef typename pqs::ratio_exp_normalise<RatioExpLhs>::type lhs_type;
      typedef typename pqs::ratio_exp_normalise<RatioExpRhs>::type rhs_type;
      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(lhs_type::exp < rhs_type::exp)>
            ,std::integral_constant<int,-1>
         ,std::integral_constant<bool,(lhs_type::exp > rhs_type::exp)>
            ,std::integral_constant<int,1>
         ,std::ratio_equal<typename lhs_type::ratio,typename rhs_type::ratio>
            ,std::integral_constant<int,0>
         ,std::ratio_greater<typename lhs_type::ratio,typename rhs_type::ratio>
            ,std::integral_constant<int,1>
         ,std::integral_constant<int,-1>
       >::type type;
       static constexpr int value = type::value;
   };

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_less : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value < 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_less_equal : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value <= 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_equal : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value == 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_not_equal : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value != 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_greater_equal : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value >= 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_greater : std::integral_constant<bool,( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value > 0 )>{}; 

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct ratio_exp_add{

      typedef typename pqs::ratio_exp_normalise<RatioExpLhs>::type lhs_type;
      typedef typename pqs::ratio_exp_normalise<RatioExpRhs>::type rhs_type;

      typedef typename ratio_exp_compare<lhs_type,rhs_type>::type comp_type;

      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(comp_type::value == 0)>,
            lhs_type,
         std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller, so adjust rhs
            pqs::detail::ratio_exp_add_exp_n<rhs_type, lhs_type::exp - rhs_type::exp>,
         pqs::detail::ratio_exp_add_exp_n<lhs_type, rhs_type::exp - lhs_type::exp>
      >::type aligned_type;

      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(comp_type::value == 0)>,
            pqs::ratio_exp<
               typename std::ratio_add<
                  typename lhs_type::ratio,
                  typename lhs_type::ratio
               >::type,
               aligned_type::exp
             >,
         std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller so use 
            pqs::ratio_exp<
               typename std::ratio_add<
                  typename lhs_type::ratio,
                  typename aligned_type::ratio
               >::type,
               aligned_type::exp
            >,
         pqs::ratio_exp<
            typename std::ratio_add<
               typename aligned_type::ratio,
               typename rhs_type::ratio
            >::type,
            aligned_type::exp
         >
      >::type result_type;

     typedef typename pqs::ratio_exp_normalise<result_type>::type type;
      
   };
}

namespace {

   void compare_test1()
   {
      typedef pqs::ratio_exp<std::ratio<1,2>,2> v1;  // 50
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v2;  // 5
      QUAN_CHECK(( pqs::ratio_exp_compare<v1,v2>::value > 0 ))

      QUAN_CHECK(( pqs::ratio_exp_compare<v2,v1>::value < 0 ))
      QUAN_CHECK(( pqs::ratio_exp_compare<v2,v2>::value == 0 ))
   }

   void compare_test2()
   {
      typedef pqs::ratio_exp<std::ratio<10,3>,3> v1; //approx 3000
      typedef pqs::ratio_exp<std::ratio<10,2>,3> v2; // 5000
      QUAN_CHECK(( pqs::ratio_exp_compare<v1,v2>::value < 0 ))
      QUAN_CHECK(( pqs::ratio_exp_compare<v2,v1>::value > 0 ))
      QUAN_CHECK(( pqs::ratio_exp_compare<v2,v2>::value == 0 ))
   }

   void compare_test3()
   {
      // different exp
      typedef pqs::ratio_exp<std::ratio<10,3>,-2> v1;  
      typedef pqs::ratio_exp<std::ratio<7,3>,-1> v2;

      QUAN_CHECK((pqs::ratio_exp_less<v1,v2>::value == true)) //f
      QUAN_CHECK((!pqs::ratio_exp_less<v2,v1>::value))

      QUAN_CHECK((pqs::ratio_exp_less_equal<v1,v2>::value)) // f
      QUAN_CHECK((!pqs::ratio_exp_less_equal<v2,v1>::value))

      QUAN_CHECK((pqs::ratio_exp_equal<v1,v1>::value))
      QUAN_CHECK((!pqs::ratio_exp_not_equal<v1,v1>::value))

      QUAN_CHECK((pqs::ratio_exp_not_equal<v1,v2>::value))
      QUAN_CHECK((pqs::ratio_exp_not_equal<v2,v1>::value))

      QUAN_CHECK((pqs::ratio_exp_greater_equal<v2,v1>::value))
      QUAN_CHECK((!pqs::ratio_exp_greater_equal<v1,v2>::value))

      QUAN_CHECK((pqs::ratio_exp_greater<v2,v1>::value))
      QUAN_CHECK((!pqs::ratio_exp_greater<v1,v2>::value))
    

            // TODO same exp
      typedef pqs::ratio_exp<std::ratio<1000,3>,-9> v3; // v3 < v4
      typedef pqs::ratio_exp<std::ratio<1001,3>,-9> v4;

      QUAN_CHECK((pqs::ratio_exp_less<v3,v4>::value))
      QUAN_CHECK((!pqs::ratio_exp_less<v4,v3>::value))

      QUAN_CHECK((pqs::ratio_exp_less_equal<v3,v4>::value)) // f
      QUAN_CHECK((!pqs::ratio_exp_less_equal<v4,v3>::value))

      QUAN_CHECK((pqs::ratio_exp_equal<v3,v3>::value))
      QUAN_CHECK((!pqs::ratio_exp_not_equal<v3,v3>::value))

      QUAN_CHECK((pqs::ratio_exp_not_equal<v3,v4>::value))
      QUAN_CHECK((pqs::ratio_exp_not_equal<v4,v3>::value))

      QUAN_CHECK((pqs::ratio_exp_greater_equal<v4,v3>::value))
      QUAN_CHECK((!pqs::ratio_exp_greater_equal<v3,v4>::value))

      QUAN_CHECK((pqs::ratio_exp_greater<v4,v3>::value))
      QUAN_CHECK((!pqs::ratio_exp_greater<v3,v4>::value))
      
   }


   void add_test1()
   {
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v1;
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v2;

      typedef pqs::ratio_exp_add<v1,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::ratio_exp<std::ratio<1>,1> >::value ))
   }

   void add_test2()
   {
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v1;
      typedef pqs::ratio_exp<std::ratio<1,2>,2> v2;

      typedef pqs::ratio_exp_add<v1,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::ratio_exp<std::ratio<11,2>,1> >::value ))

      // same test switching order
      typedef pqs::ratio_exp<std::ratio<1,2>,2> v4;
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v5;

      typedef pqs::ratio_exp_add<v4,v5> add1;
      typedef add1::type v6;

      QUAN_CHECK(( std::is_same<v6,v3>::value ))
   }

   void add_test3()
   {
   }



   void add_test()
   {
      // TODO make this a ratio exp add metafun
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v1;

      typedef pqs::ratio_exp<std::ratio<1,2>,3> v2;

      // (choose finest grained unit)

      using pqs::detail::ratio_exp_add_exp_n;

      typedef ratio_exp_add_exp_n<v2,v1::exp - v2::exp>::type t2;

      typedef pqs::detail::ratio_exp_add_values<v1,t2>::type t3;

      QUAN_CHECK(( std::is_same<t3,pqs::ratio_exp<std::ratio<101,2>,1> >::value ))
  
      typedef pqs::ratio_exp_normalise<t3>::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::ratio_exp<std::ratio<101,20>,2> >::value ))

       // make exps same
       
   }

}

void ratio_exp_test2()
{
   compare_test1();
   compare_test2();
   compare_test3();
   add_test();
   add_test1();
   add_test2();
   add_test3();
}