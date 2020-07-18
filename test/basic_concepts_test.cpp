
#include "test.hpp"
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/bool_constant.hpp>
#include <pqs/concepts/meta/equality_comparable.hpp>
#include <pqs/concepts/meta/less_than_comparable.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/meta/type_function.hpp>
#include <pqs/concepts/meta/identity_function.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/bits/implicit_cast.hpp>

namespace {

   template <bool b> struct yes_type{static constexpr bool value = b;};
   template <bool b> struct no_type{ };

   void test_meta_is_boolean_metafunction()
   {
     static_assert( pqs::meta::is_bool_constant<yes_type<true> >::value);
     static_assert( pqs::meta::is_bool_constant<yes_type<false> >::value);
     static_assert( not pqs::meta::is_bool_constant<no_type<true> >::value);
     static_assert( not pqs::meta::is_bool_constant<no_type<false> >::value);

     static_assert( pqs::meta::is_bool_constant<std::integral_constant<int,1> >::value);
     static_assert( pqs::meta::is_bool_constant<std::integral_constant<int,0> >::value);
     static_assert( pqs::meta::is_bool_constant<std::integral_constant<bool,true> >::value);
     static_assert( pqs::meta::is_bool_constant<std::integral_constant<bool,false> >::value);

     static_assert(  not pqs::meta::is_bool_constant<pqs::undefined >::value);

   }

   struct type_function_no {};
   struct type_function_yes{ typedef int type;};

   void type_function_test()
   {
       static_assert( not pqs::meta::is_type_function<type_function_no>::type::value);

       static_assert( pqs::meta::is_type_function<type_function_yes>::type::value);
   }

   struct identity{ typedef identity type;};
   struct not_identity{typedef identity type;};

   void identity_type_function_test()
   {
      static_assert( pqs::meta::is_identity_function<identity>::value );
      static_assert( not pqs::meta::is_identity_function<not_identity>::value );
   }
}

namespace my{

   template <int N>
   struct type{};
}

namespace pqs{ namespace impl{

   template <int L, int R>
   struct binary_op_impl<
      my::type<L>,pqs::equal_to,my::type<R> 
   > : std::integral_constant<bool,(L==R)>{};

   template <int L, int R>
   struct binary_op_impl<
      my::type<L>,pqs::less,my::type<R> 
   > : std::integral_constant<bool,(L < R)>{};

}}

namespace{

   void test_meta_equality_comparable()
   {
//     static_assert( pqs::meta::are_equality_comparable<int, int>::value == false);
//     static_assert( pqs::meta::are_equality_comparable<my::type<1>, my::type<2> >::value == true);
//     static_assert( pqs::meta::are_equality_comparable<my::type<-1>, my::type<-1> >::value == true);

     static_assert( pqs::meta::equality_comparable<int,int> == false);
     static_assert( pqs::meta::equality_comparable<my::type<1>, my::type<2> > == true);
     static_assert( pqs::meta::equality_comparable<my::type<-1>, my::type<-1> > == true);

   }

   void test_meta_less_than_comparable()
   {
//     static_assert( pqs::meta::are_less_than_comparable<int, int>::value == false);
//     static_assert( pqs::meta::are_less_than_comparable<my::type<1>, my::type<2>>::value == true);
//     static_assert( pqs::meta::are_less_than_comparable<my::type<-1>, my::type<-1>>::value == true);

     static_assert( pqs::meta::less_than_comparable<int,int> == false);
     static_assert( pqs::meta::less_than_comparable<my::type<1>, my::type<2> > == true);
     static_assert( pqs::meta::less_than_comparable<my::type<-1>, my::type<-1> > == true);
   }

   void test_meta_totally_ordered()
   {
     static_assert( pqs::meta::totally_ordered<int,int> == false);
     static_assert( pqs::meta::totally_ordered<my::type<1>, my::type<2> > == true);
     static_assert( pqs::meta::totally_ordered<my::type<-1>, my::type<-1> > == true);

   }

   void implicit_cast_test()
   {
        // ok, implict conversion from int to double
      auto x = pqs::implicit_cast<double>(1);
      static_assert(std::is_same_v<decltype(x),double>);
   }

   void is_defined_test()
   {
      static_assert(pqs::is_defined<double>);
      static_assert( not pqs::is_defined<pqs::undefined>);
   }

}//namespace

void basic_concepts_test()
{
   type_function_test();
   identity_type_function_test();
   test_meta_is_boolean_metafunction();
   test_meta_equality_comparable();
   test_meta_less_than_comparable();
   test_meta_totally_ordered();
   implicit_cast_test();
   is_defined_test();
}