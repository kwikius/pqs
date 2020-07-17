
#include <ratio>
#include <pqs/bits/math/fn_to_power.hpp>

namespace pqs{

   template <typename Base,typename Exp>
   struct ratio_pow;

   template <typename Base,int E>
   struct ratio_root;

   template <typename Base, typename Exp>
   struct ratio_pow {
      using type = 
         typename ratio_root< 
            typename ratio_pow<Base,std::ratio<Exp::num,1> >::type,
            Exp::den
         >::type;
   };

   template <intmax_t Bn, intmax_t Bd, intmax_t En> 
      requires (En > 1)
   struct ratio_pow<std::ratio<Bn,Bd>,std::ratio<En,1> >{
      using base_type = typename std::ratio<Bn,Bd>::type;
      using type = 
         std::ratio_multiply<
            base_type,
            typename ratio_pow<base_type,std::ratio<En-1,1> >::type
         >;
   };

   template <intmax_t Bn, intmax_t Bd, intmax_t En> 
      requires (En < 0)
   struct ratio_pow<std::ratio<Bn,Bd>,std::ratio<En,1> >{
      using base_type = typename std::ratio<Bn,Bd>::type;
      using type = 
         std::ratio_divide<
            std::ratio<1>,
            typename ratio_pow<base_type,std::ratio<-En,1> >::type
         >;
   };

   template <intmax_t Bn, intmax_t Bd, intmax_t D1> 
   struct ratio_pow<std::ratio<Bn,Bd>,std::ratio<0,D1> >{
      using type = std::ratio<1>;
   };

   template <intmax_t Bn, intmax_t Bd> 
   struct ratio_pow<std::ratio<Bn,Bd>,std::ratio<1,1> >{
      using type = typename std::ratio<Bn,Bd>::type;
   };

   template <intmax_t N, intmax_t D> 
       requires ( N != 0 )
   struct ratio_pow<std::ratio<1>,std::ratio<N,D> >{
      using type = std::ratio<1>;
   };

   template <intmax_t N, intmax_t D> 
   struct ratio_root<std::ratio<N,D>,0 >{
      using type = std::ratio<1>;
   };

   template <intmax_t N, intmax_t D> 
   struct ratio_root<std::ratio<N,D>,1 >{
      using type = typename std::ratio<N,D>::type;
   };

   template <> 
   struct ratio_root<std::ratio<4>,2 >{
      using type = std::ratio<2>;
   };

   template <>
   struct ratio_root<std::ratio<9>,2>{
      using type = std::ratio<3>;
   }; 

   template <> 
   struct ratio_root<std::ratio<16>,2 >{
      using type = std::ratio<4>;
   };

   template <> 
   struct ratio_root<std::ratio<25>,2 >{
      using type = std::ratio<5>;
   };

   template <> 
   struct ratio_root<std::ratio<36>,2 >{
      using type = std::ratio<6>;
   };

   template <> 
   struct ratio_root<std::ratio<49>,2 >{
      using type = std::ratio<7>;
   };

   template <> 
   struct ratio_root<std::ratio<64>,2 >{
      using type = std::ratio<8>;
   };

   template <> 
   struct ratio_root<std::ratio<81>,2 >{
      using type = std::ratio<9>;
   };

   template <> 
   struct ratio_root<std::ratio<100>,2 >{
      using type = std::ratio<10>;
   };

   template <intmax_t D> 
   struct ratio_root<std::ratio<1,D>,2 >{
      using type = 
         std::ratio_divide<
            std::ratio<1>, 
            typename ratio_root<std::ratio<D,1>,2>::type
         >;
   };
}

#include <iostream>

namespace {
   void bits_function();
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
   auto r2 = pqs::ratio_pow<std::ratio<1>,std::ratio<0,1> >::type();
}

template <typename Base, typename Exp>
struct ratio_root1{
   
   static constexpr auto value = std::pow(
      static_cast<double>(Base::num) / Base::den,
      static_cast<double>( Exp::num) / Exp::den
   );
};




namespace {
#if 0
void bits_function()
{
  // check_prefixable();
   namespace fps = pqs::imperial;
   
   auto q1 = fps::speed::mi_per_hr<>{10};
  
   using U1 = pqs::get_unit<decltype(q1)>;

   static_assert(pqs::is_unit_binary_op<U1>);

  // std::cout << "q1 value = " << get_numeric_value(q1) << '\n';

  // std::cout << "q1 dimension = " << 
//      unit_to_fixed_string<pqs::charset_utf8>(q1) <<'\n';

   fps::speed::ft_per_s<> q2 = q1;

  // std::cout << get_numeric_value(q2) <<'\n';

   fps::speed::mi_per_hr<> q3 = q2;

  // std::cout << get_numeric_value(q3) << '\n';
//
   auto  str2 = pqs::unit_to_fixed_string<
      pqs::get_unit<decltype(q2)>,pqs::charset_utf8
   >();
 //  std::cout << "(should be ft/s) " << str2 <<'\n';

   auto  str1 = pqs::unit_to_fixed_string<
      pqs::charset_utf8
   >(q1);
  // std::cout << "(should be mi/hr) " << str1 <<'\n';

   pqs::imperial::time::min<> q4{3};
   
   auto str4 =  pqs::unit_to_fixed_string<
      pqs::charset_utf8
   >(q4);

  // std::cout << str4 <<'\n';

   fps::length::yd<> q5{1};

   using U5 = pqs::get_unit<decltype(q5)>;

   q1 = q5 / q4;

  // std::cout << get_numeric_value(q1) << '\n';

   auto q6 = q5 * q4;

   auto str6 = pqs::unit_to_fixed_string<
      pqs::charset_utf8
   >(q6);
//   std::cout << "str6 = " <<  str6 << '\n';
//   std::cout << " yd has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::yd<> >,pqs::charset_ascii > << '\n';
//   std::cout << " ft has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::ft<> >,pqs::charset_ascii > << '\n';
//   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_utf8> <<'\n';
//   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_ascii> <<'\n';
//   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_utf8> <<'\n';
//   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_ascii> <<'\n';
  

   using q_type = pqs::imperial::length::mi<> ;
//   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
//      pqs::get_conversion_factor<q_type>,
//      pqs::charset_utf8
//   >() <<'\n';

//   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
//      pqs::get_conversion_factor<q_type>,
//      pqs::charset_ascii
//   >() <<'\n';
//;
//
//   std::cout << "eval q_type = " << pqs::evaluate<pqs::get_conversion_factor<q_type> >() <<'\n';

   using q_type1 = pqs::imperial::length::ft<> ;
//   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
//      pqs::get_conversion_factor<q_type1>,
//      pqs::charset_utf8
//   >() <<'\n';

//   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
//      pqs::get_conversion_factor<q_type1>,
//      pqs::charset_ascii
//   >() <<'\n';
//   std::cout << "eval q_type1 cf = " << static_cast<double>(pqs::evaluate<pqs::get_conversion_factor<q_type1> >()) <<'\n';

   auto cf3 = std::ratio<7,3>() ^ pqs::exponent10<26,7>();

//   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
//      decltype(cf3),
//      pqs::charset_utf8
//   >() << '\n';
//   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
//      decltype(cf3),
//      pqs::charset_ascii
//   >() << '\n';
}
#endif

}