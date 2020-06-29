
#include "test.hpp"

#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/binary_op.hpp>

#include <iostream>

namespace {

   template <intmax_t N, intmax_t D>
   std::ostream & operator << (std::ostream & os, std::ratio<N,D> v)
   {
      return os << "{ " << N << " / " << D << " }" ;
   }

   template <typename M, typename E>
   std::ostream & operator << (std::ostream & os, pqs::conversion_factor<M,E> v)
   {
      return os << typename decltype(v)::multiplier{} << " ^ " << typename decltype(v)::exponent{} ;
   }

   template <typename CF>
   inline constexpr typename pqs::conversion_factor_eval<CF>::type
   eval_cf()
   {
      return pqs::conversion_factor_eval<CF>{}();
   }

   template <typename CFL, typename CFR>
   inline constexpr bool same_cf()
   {
      return eval_cf<CFL>() == eval_cf<CFR>() ;
   }

   template <typename CF>
   void show_cf()
   {
      std::cout << CF{} << " == " << pqs::conversion_factor_eval<CF>{}() ;
   }
   
   void compare_test1()
   {
      typedef pqs::detail::ll_conversion_factor<std::ratio<1,2>,std::ratio<2> > v1;  // 50
      typedef pqs::detail::ll_conversion_factor<std::ratio<1,2>,std::ratio<1> > v2;  // 5

      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v1,v2>::value > 0 ))
      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v2,v1>::value < 0 ))
      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v2,v2>::value == 0 ))

      typedef pqs::detail::to_conversion_factor<v1>::type v1a;
      typedef pqs::detail::to_conversion_factor<v2>::type v2a;

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::less,v2a>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::less,v1a>::value == true) )

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::less_equal,v2a>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::less_equal,v1a>::value == true) )

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::equal_to,v2a>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::equal_to,v1a>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::equal_to,v1a>::value ==true) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::equal_to,v2a>::value ==true) )

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::not_equal_to,v2a>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::not_equal_to,v1a>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::not_equal_to,v1a>::value == false) )

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::greater_equal,v2a>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::greater_equal,v1a>::value == false) )

      QUAN_CHECK( ( pqs::binary_op<v1a,pqs::greater,v2a>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2a,pqs::greater,v1a>::value == false) )

   }

   void compare_test2()
   {
      typedef pqs::detail::ll_conversion_factor<std::ratio<10,3>,std::ratio<3> > v1; //approx 3000
      typedef pqs::detail::ll_conversion_factor<std::ratio<10,2>,std::ratio<3> > v2; // 5000
      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v1,v2>::value < 0 ))
      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v2,v1>::value > 0 ))
      QUAN_CHECK(( pqs::detail::ll_conversion_factor_compare<v2,v2>::value == 0 ))
   }

   void compare_test3()
   {
      // different exp
      typedef pqs::conversion_factor<std::ratio<10,3>,pqs::exponent10<-2> > v1;  
      typedef pqs::conversion_factor<std::ratio<7,3>,pqs::exponent10<-1> > v2;

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
      typedef pqs::conversion_factor<std::ratio<1000,3>,pqs::exponent10<-9> > v3; // v3 < v4
      typedef pqs::conversion_factor<std::ratio<1001,3>,pqs::exponent10<-9> > v4;

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
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<1> > v1;
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<1> > v2;

      typedef pqs::binary_op<v1,pqs::plus,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<1>,pqs::exponent10<1> > >::value ))
   }

   void add_test2()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<1> > v1;
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<2> > v2;

      typedef pqs::binary_op<v1,pqs::plus,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<11,2>,pqs::exponent10<1> > >::value ))

      // same test switching order
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<2> > v4;
      typedef pqs::conversion_factor<std::ratio<1,2>,pqs::exponent10<1> > v5;

      typedef pqs::binary_op<v4,pqs::plus,v5> add1;
      typedef add1::type v6;

      QUAN_CHECK(( std::is_same<v6,v3>::value ))
   }

   void add_test3()
   {
     //QUAN_CHECK(false)
   }

   void add_test()
   {

      typedef pqs::detail::ll_conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;

      typedef pqs::detail::ll_conversion_factor<std::ratio<1,2>,std::ratio<3> > v2;

      using pqs::detail::ll_conversion_factor_add_exp_n;

      typedef ll_conversion_factor_add_exp_n<v2,v1::exponent::num - v2::exponent::num>::type t2;

      typedef pqs::detail::ll_conversion_factor_add_values<v1,t2>::type t3;

      QUAN_CHECK(( std::is_same<t3,pqs::detail::ll_conversion_factor<std::ratio<101,2>,std::ratio<1> > >::value ))
  
      typedef pqs::detail::ll_conversion_factor_normalise<t3>::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::detail::ll_conversion_factor<std::ratio<101,20>,std::ratio<2> > >::value ))

   }

  /** 
   *  normalised conversion factor has multiplier >= 1 and muliplier >10
   */
   void normalise_test1()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<1,100>,
         pqs::exponent10<-3>
      >;

      using cf2 = pqs::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<-5> >::value) )
   }

   void normalise_test2()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<99,1>,
         pqs::exponent10<7>
      >;

      using cf2 = pqs::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<99,10> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<8> >::value) )
   }

   void normalise_test3()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<1>,
         pqs::exponent10<0>
      >;

      using cf2 = pqs::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<0> >::value) )
   }

   void normalise_test4()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<10000>,
         pqs::exponent10<0>
      >;

      using cf2 = pqs::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<4> >::value) )
   }

   void normalise_test5()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<12345>,
         pqs::exponent10<0>
      >;

      using cf2 = pqs::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<2469,2000> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<4> >::value) )
   }

   void normalise_test6()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<12345>,
         pqs::exponent10<1,2>
      >;
   
      using cf2 = pqs::conversion_factor_normalise<cf1>::type;
      
      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<2469,2000> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,pqs::exponent10<9,2> >::value) )
   }

   void multiply_test1()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<6>,
         pqs::exponent10<3>
      >;

      using cf2 = pqs::conversion_factor<
         std::ratio<7>,
         pqs::exponent10<2>
      >;

      typedef pqs::binary_op<cf1, pqs::times,cf2>::type res;

      QUAN_CHECK( (std::is_same<res::multiplier,std::ratio<21,5> >::value) )
      QUAN_CHECK( (std::is_same<res::exponent,pqs::exponent10<6> >::value) )
   
   }

   void multiply_test2()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<10>,
         pqs::exponent10<-1>
      >;

      using cf2 = pqs::conversion_factor<
         std::ratio<100>,
         pqs::exponent10<-2>
      >;

      typedef pqs::binary_op<cf1, pqs::times,cf2>::type res;

      QUAN_CHECK( (std::is_same<res::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<res::exponent,pqs::exponent10<0> >::value) )
   }

  void multiply_test3()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<997>,
         pqs::exponent10<-3>
      >;

      using cf2 = pqs::conversion_factor<
         std::ratio<56,97>,
         pqs::exponent10<-2>
      >;

      typedef pqs::binary_op<cf1,pqs::times,cf2>::type res;

      QUAN_CHECK( (std::is_same<res::multiplier,std::ratio<13958,2425> >::value) )
      QUAN_CHECK( (std::is_same<res::exponent,pqs::exponent10<-3> >::value) )

      auto v1 = eval_cf<cf1>();
      auto v2 = eval_cf<cf2>();
      auto v3 = eval_cf<res>();

      QUAN_CHECK ( (abs(v3 - v1 * v2) < 1.e-6) )
   }

   void divide_test1()
   {
     using cf1 = pqs::conversion_factor<
         std::ratio<997>,
         pqs::exponent10<-3>
      >;

      using cf2 = pqs::conversion_factor<
         std::ratio<56,97>,
         pqs::exponent10<-2>
      >;

      typedef pqs::binary_op<cf1,pqs::divides,cf2>::type res;

      QUAN_CHECK( (std::is_same<res::multiplier,std::ratio< 96709 , 56000> >::value) )
      QUAN_CHECK( (std::is_same<res::exponent,pqs::exponent10<2> >::value) )
    
      auto v1 = eval_cf<cf1>();
      auto v2 = eval_cf<cf2>();
      auto v3 = eval_cf<res>();

      QUAN_CHECK ( (abs(v3 - v1 / v2) < 1.e-6) )
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

   normalise_test1();
   normalise_test2();
   normalise_test3();
   normalise_test4();
   normalise_test5();
   normalise_test6();

   multiply_test1();
   multiply_test2();
   multiply_test3();

   divide_test1();
}