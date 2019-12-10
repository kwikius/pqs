

#include <quan_matters/test/test.hpp>

#include <pqs/bits/ratio_exp.hpp>

namespace pqs {

   namespace detail{


      // return 1 if  lhs > rhs
      // return 0 if Lhs == Rhs,
      // return -1 if lhs < rhs
      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_compare{
         typedef typename ratio_exp_normalise<RatioExpLhs>::type lhs_type;
         typedef typename ratio_exp_normalise<RatioExpRhs>::type rhs_type;
         typedef typename pqs::meta::eval_if<
            std::bool_constant<(lhs_type::exp < rhs_type::exp)>
               ,std::integral_constant<int,-1>
            ,std::bool_constant<(lhs_type::exp > rhs_type::exp)>
               ,std::integral_constant<int,1>
            ,std::ratio_equal<typename lhs_type::ratio,typename rhs_type::ratio>
               ,std::integral_constant<int,0>
            ,std::ratio_greater<typename lhs_type::ratio,typename rhs_type::ratio>
               ,std::integral_constant<int,1>
            ,std::integral_constant<int,-1>
          >::type type;
          static constexpr bool value = type::value;
      };

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_less : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value < 0 )>{};

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_less_equal : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value <= 0 )>{};

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_equal : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value == 0 )>{};

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_not_equal : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value != 0 )>{};

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_greater_equal : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value >= 0 )>{};

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct ratio_exp_greater : std::bool_constant<( ratio_exp_compare<RatioExpLhs, RatioExpRhs>::value > 0 )>{}; 
   }
}

namespace {

   void compare_test1()
   {
      typedef pqs::ratio_exp<std::ratio<1,2>,2> v1;
      typedef pqs::ratio_exp<std::ratio<1,2>,1> v2;
      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v1,v2>::value > 0 ))

      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v2,v1>::value > 0 ))
      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v2,v2>::value == 0 ))

      
      
   }

   void compare_test2()
   {
      typedef pqs::ratio_exp<std::ratio<10,3>,10> v1;
      typedef pqs::ratio_exp<std::ratio<1,2>,10> v2;
      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v1,v2>::value > 0 ))

      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v2,v1>::value > 0 ))
      QUAN_CHECK(( pqs::detail::ratio_exp_compare<v2,v2>::value == 0 ))
      
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
  
      typedef pqs::detail::ratio_exp_normalise<t3>::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::ratio_exp<std::ratio<101,200>,3> >::value ))

       // make exps same
       

   }

}

void ratio_exp_test2()
{
   compare_test1();
   add_test();
}