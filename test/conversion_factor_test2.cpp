
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

   template <typename CFL, typename CFR>
   bool same_cf()
   {
       return  pqs::conversion_factor_eval<CFL>{}() == pqs::conversion_factor_eval<CFR>{}() ;
   }

   template <typename CF>
   void show_cf()
   {
      std::cout << CF{} << " == " << pqs::conversion_factor_eval<CF>{}() ;
   }
   
   void compare_test1()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v1;  // 50
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v2;  // 5

      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v1,v2>::value > 0 ))

      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v1>::value < 0 ))
      QUAN_CHECK(( pqs::detail::conversion_factor_compare<v2,v2>::value == 0 ))


      QUAN_CHECK( ( pqs::binary_op<v1,pqs::less,v2>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::less,v1>::value == true) )

      QUAN_CHECK( ( pqs::binary_op<v1,pqs::less_equal,v2>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::less_equal,v1>::value == true) )

      QUAN_CHECK( ( pqs::binary_op<v1,pqs::equal_to,v2>::value == false) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::equal_to,v1>::value == false) )

      QUAN_CHECK( ( pqs::binary_op<v1,pqs::not_equal_to,v2>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::not_equal_to,v1>::value == true) )

      QUAN_CHECK( ( pqs::binary_op<v1,pqs::greater_equal,v2>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::greater_equal,v1>::value == false) )

      QUAN_CHECK( ( pqs::binary_op<v1,pqs::greater,v2>::value == true) )
      QUAN_CHECK( ( pqs::binary_op<v2,pqs::greater,v1>::value == false) )

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

      typedef pqs::binary_op<v1,pqs::plus,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<1>,std::ratio<1> > >::value ))
   }

   void add_test2()
   {
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v2;

      typedef pqs::binary_op<v1,pqs::plus,v2> add;
      typedef add::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<11,2>,std::ratio<1> > >::value ))

      // same test switching order
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<2> > v4;
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v5;

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
      // TODO make this a ratio exp add metafun
      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<1> > v1;

      typedef pqs::conversion_factor<std::ratio<1,2>,std::ratio<3> > v2;

      // (choose finest grained unit)

      using pqs::detail::conversion_factor_add_exp_n;

      typedef conversion_factor_add_exp_n<v2,v1::exponent::num - v2::exponent::num>::type t2;

      typedef pqs::detail::conversion_factor_add_values<v1,t2>::type t3;

      QUAN_CHECK(( std::is_same<t3,pqs::conversion_factor<std::ratio<101,2>,std::ratio<1> > >::value ))
  
      typedef pqs::detail::conversion_factor_normalise<t3>::type v3;

      QUAN_CHECK(( std::is_same<v3,pqs::conversion_factor<std::ratio<101,20>,std::ratio<2> > >::value ))

   }

  /** 
   *  normalised conversion factor has multiplier >= 1 and muliplier >10
   */
   void normalise_test1()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<1,100>,
         pqs::unit_exp<-3>
      >;

      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<-5> >::value) )
   }

  

   void normalise_test2()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<99,1>,
         pqs::unit_exp<7>
      >;

      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<99,10> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<8> >::value) )
   }

   void normalise_test3()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<1>,
         pqs::unit_exp<0>
      >;

      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<0> >::value) )
   }

   void normalise_test4()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<10000>,
         pqs::unit_exp<0>
      >;

      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<1> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<4> >::value) )
   }

   void normalise_test5()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<12345>,
         pqs::unit_exp<0>
      >;

      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;

      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<2469,2000> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<4> >::value) )
   }

   void normalise_test6()
   {
      using cf1 = pqs::conversion_factor<
         std::ratio<12345>,
         pqs::unit_exp<1,2>
      >;
   
      using cf2 = pqs::detail::conversion_factor_normalise<cf1>::type;
      
      QUAN_CHECK( (same_cf<cf1,cf2>()) )
      QUAN_CHECK( (std::is_same<cf2::multiplier,std::ratio<2469,2000> >::value) )
      QUAN_CHECK( (std::is_same<cf2::exponent,std::ratio<9,2> >::value) )
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
}