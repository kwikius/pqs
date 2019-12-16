
#include "test.hpp"

#include <pqs/concepts/meta/bool_constant.hpp>
#include <pqs/concepts/meta/equality_comparable.hpp>
#include <pqs/concepts/meta/less_than_comparable.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/meta/is_type_function.hpp>
#include <pqs/bits/undefined.hpp>

namespace {

   template <bool b> struct yes_type{static constexpr bool value = b;};
   template <bool b> struct no_type{ };

   void test_meta_is_boolean_metafunction()
   {
      QUAN_CHECK((pqs::meta::is_bool_constant<yes_type<true> >::value))
      QUAN_CHECK((pqs::meta::is_bool_constant<yes_type<false> >::value))
      QUAN_CHECK((not pqs::meta::is_bool_constant<no_type<true> >::value))
      QUAN_CHECK((not pqs::meta::is_bool_constant<no_type<false> >::value))

      QUAN_CHECK((pqs::meta::is_bool_constant<std::integral_constant<int,1> >::value))
      QUAN_CHECK((pqs::meta::is_bool_constant<std::integral_constant<int,0> >::value))
      QUAN_CHECK((pqs::meta::is_bool_constant<std::integral_constant<bool,true> >::value))
      QUAN_CHECK((pqs::meta::is_bool_constant<std::integral_constant<bool,false> >::value))

      QUAN_CHECK(( not pqs::meta::is_bool_constant<pqs::undefined >::value))

    #if defined __cpp_concepts

      QUAN_CHECK((pqs::meta::bool_constant<yes_type<true> >))
      QUAN_CHECK((pqs::meta::bool_constant<yes_type<false> >))
      QUAN_CHECK((not pqs::meta::bool_constant<no_type<true> >))
      QUAN_CHECK((not pqs::meta::bool_constant<no_type<false> >))

      QUAN_CHECK((pqs::meta::bool_constant<std::integral_constant<int,1> >))
      QUAN_CHECK((pqs::meta::bool_constant<std::integral_constant<int,0> >))
      QUAN_CHECK((pqs::meta::bool_constant<std::integral_constant<bool,true> >))
      QUAN_CHECK((pqs::meta::bool_constant<std::integral_constant<bool,false> >))

    #endif
   }

   struct type_function_no {};
   struct type_function_yes{ typedef int type;};

   void type_function_test()
   {
       QUAN_CHECK ( ( not pqs::meta::detail::is_type_function<type_function_no>::type::value) )

       QUAN_CHECK ( ( pqs::meta::detail::is_type_function<type_function_yes>::type::value) )
   }
}

namespace my{

   template <int N>
   struct type{};
}

namespace pqs{ namespace impl{

   template <int L, int R>
   struct binary_op_impl<
      my::type<L>,pqs::meta::equal_to,my::type<R> 
   > : std::integral_constant<bool,(L==R)>{};

   template <int L, int R>
   struct binary_op_impl<
      my::type<L>,pqs::meta::less,my::type<R> 
   > : std::integral_constant<bool,(L < R)>{};

}}

namespace{

   void test_meta_equality_comparable()
   {
      QUAN_CHECK((pqs::meta::are_equality_comparable<int, int>::value == false))
      QUAN_CHECK((pqs::meta::are_equality_comparable<my::type<1>, my::type<2> >::value == true))
      QUAN_CHECK((pqs::meta::are_equality_comparable<my::type<-1>, my::type<-1> >::value == true))

     #if defined __cpp_concepts

      QUAN_CHECK((pqs::meta::equality_comparable<int,int> == false))
      QUAN_CHECK((pqs::meta::equality_comparable<my::type<1>, my::type<2> > == true))
      QUAN_CHECK((pqs::meta::equality_comparable<my::type<-1>, my::type<-1> > == true))

     #endif

   }

   void test_meta_less_than_comparable()
   {
      QUAN_CHECK((pqs::meta::are_less_than_comparable<int, int>::value == false))
      QUAN_CHECK((pqs::meta::are_less_than_comparable<my::type<1>, my::type<2>>::value == true))
      QUAN_CHECK((pqs::meta::are_less_than_comparable<my::type<-1>, my::type<-1>>::value == true))

     #if defined __cpp_concepts

      QUAN_CHECK((pqs::meta::less_than_comparable<int,int> == false))
      QUAN_CHECK((pqs::meta::less_than_comparable<my::type<1>, my::type<2> > == true))
      QUAN_CHECK((pqs::meta::less_than_comparable<my::type<-1>, my::type<-1> > == true))

     #endif
   }

   void test_meta_totally_ordered()
   {
      QUAN_CHECK((pqs::meta::are_totally_ordered<int, int>::value == false))
      QUAN_CHECK((pqs::meta::are_totally_ordered<my::type<1>, my::type<2>>::value == true))
      QUAN_CHECK((pqs::meta::are_totally_ordered<my::type<-1>, my::type<-1>>::value == true))

     #if defined __cpp_concepts

      QUAN_CHECK((pqs::meta::totally_ordered<int,int> == false))
      QUAN_CHECK((pqs::meta::totally_ordered<my::type<1>, my::type<2> > == true))
      QUAN_CHECK((pqs::meta::totally_ordered<my::type<-1>, my::type<-1> > == true))

     #endif
   }

}//namespace

void basic_concepts_test()
{
   type_function_test();
   test_meta_is_boolean_metafunction();
   test_meta_equality_comparable();
   test_meta_less_than_comparable();
   test_meta_totally_ordered();
}