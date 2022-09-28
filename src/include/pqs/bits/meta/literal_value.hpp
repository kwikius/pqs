#ifndef PQS_META_LITERAL_VALUE_HPP_INCLUDED
#define PQS_META_LITERAL_VALUE_HPP_INCLUDED

#include <limits>
#include <type_traits>

#include <pqs/bits/meta/eval_if.hpp>
#include <pqs/bits/meta/identity.hpp>
#include <pqs/bits/meta/is_narrowing_conversion.hpp>
#include <pqs/bits/meta/narrowest_int.hpp>
#include <pqs/bits/meta/is_digit.hpp>
#include <pqs/bits/undefined.hpp>

namespace pqs::meta::detail{

   enum class udl_number_style { Int, Float, Undefined};

   template <char... C>
   struct udl_get_number;

   template <char... C>
   struct udl_get_int;

   template <char Cf, char... C>
     requires pqs::meta::is_digit<Cf>
   struct udl_get_int<Cf,C...>{
      static unsigned long long constexpr multiplier = 10ULL * udl_get_int<C...>::multiplier;
     // static constexpr unsigned int num_digits_after_point = 0U;
      static unsigned long long constexpr value =
         (static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0')) * multiplier + udl_get_int<C...>::value;
   };

   template <char... C>

   struct udl_get_int<'\'',C...>{
      static unsigned long long constexpr multiplier = udl_get_int<C...>::multiplier;
      static unsigned long long constexpr value = udl_get_int<C...>::value;
   };

   template <char Cf>
      requires pqs::meta::is_digit<Cf>
   struct udl_get_int<Cf>{
      static unsigned constexpr multiplier = 1U;
    //  static constexpr unsigned int num_digits_after_point = 0U;
      static unsigned int constexpr value = static_cast<unsigned int>(Cf) - static_cast<unsigned int>('0');
   };

   template<>
   struct udl_get_number<'.'>{
      static long double constexpr value = 0.0;
      static constexpr unsigned int num_digits_after_point = 0U;
      static constexpr unsigned int multiplier = 1U;
      static constexpr udl_number_style style = udl_number_style::Float;
   };

   template<char C>
     requires pqs::meta::is_digit<C>
   struct udl_get_number<C>{
      static constexpr auto value = udl_get_int<C>::value;
      static constexpr unsigned int multiplier = 1U;
      static constexpr unsigned int num_digits_after_point = 0U;
      static constexpr udl_number_style style = udl_number_style::Int;
   };

   long double constexpr shiftpoint( long double v){
      return v >= 1.0 ? shiftpoint(v / 10) : v;
   };

   template<char ...C>
   struct udl_get_number<'.',C...>{
      static long double constexpr value =
         shiftpoint( static_cast<long double>(udl_get_int<C...>::value));
      static constexpr unsigned int num_digits_after_point = sizeof...(C);
      static constexpr unsigned int multiplier = 1U;
      static constexpr udl_number_style style = udl_number_style::Float;
   };



   template<char Cf,char... C>
      requires pqs::meta::is_digit<Cf> && (udl_get_number<C...>::style == udl_number_style::Float)
   struct udl_get_number<Cf,C...>{
      static long double constexpr value = udl_get_int<Cf>::value *
           udl_get_number<C...>::multiplier + udl_get_number<C...>::value;
      static unsigned long long constexpr multiplier
        = udl_get_number<C...>::multiplier * 10;
      static constexpr unsigned int num_digits_after_point
        = udl_get_number<C...>::num_digits_after_point;
      static constexpr udl_number_style style = udl_number_style::Float;
   };

   template<char... C>
      requires ( udl_get_number<C...>::style == udl_number_style::Float )
   struct udl_get_number<'\'',C...>{
      static long double constexpr value = udl_get_number<C...>::value;
      static unsigned long long constexpr multiplier
        = udl_get_number<C...>::multiplier;
      static constexpr unsigned int num_digits_after_point
        = udl_get_number<C...>::num_digits_after_point;
      static constexpr udl_number_style style = udl_number_style::Float;
   };

   template<char Cf,char... C>
      requires pqs::meta::is_digit<Cf> && (udl_get_number<C...>::style == udl_number_style::Int)
   struct udl_get_number<Cf,C...>{
      static constexpr auto value = udl_get_int<Cf,C...>::value;
      static constexpr unsigned int num_digits_after_point = 0U;
      static constexpr udl_number_style style = udl_number_style::Int;
   };
   /**
    * @todo make sure that precision is not truncated.
    * Decide on basis of number of digits after decimal.
    * The exact values per type we can argue about. Also provides a way to force a type,
    * though the other way would just be to add a postfix.
    * Note If you need higher precision, you can always declare your literal
    * as my_quantity{1.234567890}. Generally UDLs are useful for init by 0 or 1 etc.
    * Ultimately the UDL is a convenience.
   **/

   template <typename T>
   struct udl_max_digits_after_point ;

   template <>
   struct udl_max_digits_after_point<float> { static constexpr unsigned int value = 6U;};

   template <>
   struct udl_max_digits_after_point<double> { static constexpr unsigned int value = 12U;};

} // pqs::meta::detail

namespace pqs::meta{

   template <char... V>
   auto constexpr literal_value()
   {
       auto constexpr value = pqs::meta::detail::udl_get_number<V...>::value;
       auto constexpr num_digits_after_point = pqs::meta::detail::udl_get_number<V...>::num_digits_after_point;
       // N.B. This could be done better from the point of view of precision
       // and deciding which floating point type to return, but at this point
       // it is just a question of verifying that it works
       // and that you can return different types of floats from this function
       if constexpr (std::is_floating_point_v<decltype(value)>){
         if constexpr ( (num_digits_after_point <= pqs::meta::detail::udl_max_digits_after_point<float>::value) &&
            (value < std::numeric_limits<float>::max()) ){
            return static_cast<float>(value);
         }else if constexpr (  (num_digits_after_point <= pqs::meta::detail::udl_max_digits_after_point<double>::value) &&
            (  value < std::numeric_limits<double>::max())){
            return static_cast<double> (value);
         }else{
            return static_cast<long double>(value);
         }
       }else{
          using number_type = pqs::meta::narrowest_int<value>;
          return static_cast<number_type>(value);
       }
   }

}//pqs::meta


#endif // PQS_META_LITERAL_VALUE_HPP_INCLUDED
