

#include "test.hpp"

#include <pqs/bits/conversion_factor.hpp>
#include <pqs/bits/binary_op.hpp>

#include <iostream>

namespace pqs {


   namespace detail{

   // return 1 if  lhs > rhs
   // return 0 if Lhs == Rhs,
   // return -1 if lhs < rhs

      template <typename RatioExpLhs, typename RatioExpRhs>
      struct conversion_factor_compare{
         typedef typename pqs::conversion_factor_normalise<RatioExpLhs>::type lhs_type;
         typedef typename pqs::conversion_factor_normalise<RatioExpRhs>::type rhs_type;
         typedef typename pqs::meta::eval_if<
            std::ratio_less<typename lhs_type::exponent,typename rhs_type::exponent>,
               std::integral_constant<int,-1>,
            std::ratio_greater<typename lhs_type::exponent,typename rhs_type::exponent>,
               std::integral_constant<int,1>,
            std::ratio_equal<typename lhs_type::multiplier,typename rhs_type::multiplier>,
               std::integral_constant<int,0>,
            std::ratio_greater<typename lhs_type::multiplier,typename rhs_type::multiplier>,
               std::integral_constant<int,1>,
            std::integral_constant<int,-1>
         >::type type;
         static constexpr int value = type::value;
      };
   }

   namespace impl{

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::less,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value < 0)>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::less_equal,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value <= 0)>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::equal_to,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value == 0)>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::not_equal_to,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value != 0)>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::greater_equal,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value >= 0)>{};

      template <typename Lhs, typename Rhs>
      struct binary_op_impl<
         Lhs, pqs::greater,Rhs,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::meta::is_conversion_factor<Lhs>,
               pqs::meta::is_conversion_factor<Rhs>
            >
         >::type
        > : std::integral_constant<bool, (pqs::detail::conversion_factor_compare<Lhs,Rhs>::value > 0)>{};

   } // impl
/*
   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_less : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value < 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_less_equal : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value <= 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_equal : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value == 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_not_equal : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value != 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_greater_equal : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value >= 0 )>{};

   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_greater : std::integral_constant<bool,( conversion_factor_compare<RatioExpLhs, RatioExpRhs>::value > 0 )>{}; 
*/
   // addition of two conv  
   // only possible for rational powers if both  have same denominator
   template <typename RatioExpLhs, typename RatioExpRhs>
   struct conversion_factor_add{

      typedef typename pqs::conversion_factor_normalise<RatioExpLhs>::type lhs_type;
      typedef typename pqs::conversion_factor_normalise<RatioExpRhs>::type rhs_type;

      typedef typename detail::conversion_factor_compare<lhs_type,rhs_type>::type comp_type;

      // align the conversion_factors so that the exponents are the same
      // N.B this can only work if the conversion_factor::exponent denominators are the same
      static_assert(RatioExpLhs::exponent::den == RatioExpRhs::exponent::den, "conversion_factor add: Exponent::denoms must be same");
      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(comp_type::value == 0)>,
            lhs_type,
         std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller, so adjust rhs
            pqs::detail::conversion_factor_add_exp_n<rhs_type, lhs_type::exponent::num - rhs_type::exponent::num>,
         pqs::detail::conversion_factor_add_exp_n<lhs_type, rhs_type::exponent::num - lhs_type::exponent::num>
      >::type aligned_type;

      typedef typename pqs::meta::eval_if<
         std::integral_constant<bool,(comp_type::value == 0)>,
            pqs::conversion_factor<
               typename std::ratio_add<
                  typename lhs_type::multiplier,
                  typename lhs_type::multiplier
               >::type,
               typename aligned_type::exponent
             >,
         std::integral_constant<bool,(comp_type::value < 0)>,  // lhs is smaller so use 
            pqs::conversion_factor<
               typename std::ratio_add<
                  typename lhs_type::multiplier,
                  typename aligned_type::multiplier
               >::type,
               typename aligned_type::exponent
            >,
         pqs::conversion_factor<
            typename std::ratio_add<
               typename aligned_type::multiplier,
               typename rhs_type::multiplier
            >::type,
            typename aligned_type::exponent
         >
      >::type result_type;

     typedef typename pqs::conversion_factor_normalise<result_type>::type type;
      
   };
}

namespace {

   void compare_test1()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v1;  // 50
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v2;  // 5
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v1,v2>::value > 0 ))

      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v1>::value < 0 ))
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v2>::value == 0 ))
   }

   void compare_test2()
   {
      typedef pqs::conversion_factor<std::ratio<10,3>,std::ratio<3> > v1; //approx 3000
      typedef pqs::conversion_factor<std::ratio<10,2>,std::ratio<3> > v2; // 5000
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v1,v2>::value < 0 ))
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v1>::value > 0 ))
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v2>::value == 0 ))
   }

   void compare_test3()
   {
      // different exp
      typedef pqs::conversion_factor<std::ratio<10,3>,std::ratio<-2> > v1;  
      typedef pqs::conversion_factor<std::ratio<7,3>,std::ratio<-1> > v2;

      QUAN_CHECK((pqs::binary_op<v1,pqs::less,v2>::value == true)) //f
      QUAN_CHECK((!pqs::binary_op<v2,pqs::less,v1>::value))

      QUAN_CHECK((pqs::binary_op<v1,pqs::less_equal,v2>::value)) // f
      QUAN_CHECK((!pqs::binary_op<v2,pqs::less_equal,v1>::value))

      QUAN_CHECK((pqs::binary_op<v1,pqs::equal_to,v1>::value))
      QUAN_CHECK((!pqs::binary_op<v1,pqs::not_equal_to,v1>::value))

      QUAN_CHECK((pqs::binary_op<v1,pqs::not_equal_to,v2>::value))
      QUAN_CHECK((pqs::binary_op<v2,pqs::not_equal_to,v1>::value))

      QUAN_CHECK((pqs::binary_op<v2,pqs::greater_equal,v1>::value))
      QUAN_CHECK((!pqs::binary_op<v1,pqs::greater_equal,v2>::value))

      QUAN_CHECK((pqs::binary_op<v2,pqs::greater,v1>::value))
      QUAN_CHECK((!pqs::binary_op<v1,pqs::greater,v2>::value))
    

            // TODO same exp
      typedef pqs::conversion_factor<std::ratio<1000,3>,std::ratio<-9> > v3; // v3 < v4
      typedef pqs::conversion_factor<std::ratio<1001,3>,std::ratio<-9> > v4;

      QUAN_CHECK((pqs::binary_op<v3,pqs::less,v4>::value))
      QUAN_CHECK((!pqs::binary_op<v4,pqs::less,v3>::value))

      QUAN_CHECK((pqs::binary_op<v3,pqs::less_equal,v4>::value)) // f
      QUAN_CHECK((!pqs::binary_op<v4,pqs::less_equal,v3>::value))

      QUAN_CHECK((pqs::binary_op<v3,pqs::equal_to,v3>::value))
      QUAN_CHECK((!pqs::binary_op<v3,pqs::greater,v3>::value))

      QUAN_CHECK((pqs::binary_op<v3,pqs::not_equal_to,v4>::value))
      QUAN_CHECK((pqs::binary_op<v4,pqs::not_equal_to,v3>::value))

      QUAN_CHECK((pqs::binary_op<v4,pqs::greater_equal,v3>::value))
      QUAN_CHECK((!pqs::binary_op<v3,pqs::greater_equal,v4>::value))

      QUAN_CHECK((pqs::binary_op<v4,pqs::greater,v3>::value))
      QUAN_CHECK((!pqs::binary_op<v3,pqs::greater,v4>::value))
      
   }


   void add_test1()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v2;

      typedef pqs::conversion_factor_add<v1,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<1>,std::ratio<1> > >::value ))
   }

   void add_test2()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v2;

      typedef pqs::conversion_factor_add<v1,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<11,2>,std::ratio<1> > >::value ))

      // same test switching order
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v4;
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v5;

      typedef pqs::conversion_factor_add<v4,v5> add1;
      typedef add1::type v6;

      QUAN_CHECK(( std::is_same<v6,v3>::value ))
   }

   void add_test3()
   {
     //QUAN_CHECK(false)
   }



   void add_test()
   {
      // TODO make this a ratio exp add metafun
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;

      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<3> > v2;

      // (choose finest grained unit)

      using pqs::detail::conversion_factor_add_exp_n;

      typedef conversion_factor_add_exp_n<v2,v1::exponent::num - v2::exponent::num>::type t2;

      typedef pqs::detail::conversion_factor_add_values<v1,t2>::type t3;

      QUAN_CHECK(( std::is_same<t3,pqs::conversion_factor<std::ratio<101,2>,std::ratio<1> > >::value ))
  
      typedef pqs::conversion_factor_normalise<t3>::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<101,20>,std::ratio<2> > >::value ))

       // make exps same
       
   }

}

void conversion_factor_test2()
{
   compare_test1();
   compare_test2();
   compare_test3();
   add_test();
   add_test1();
   add_test2();
   add_test3();
}