

#include <pqs/bits/base_quantities.hpp>

#include <pqs/instance/basic_quantity.hpp>
#include <pqs/bits/basic_unit.hpp>

struct dummy_system{};

namespace pqs{

   template <int N>
   struct exponent10_t{

      template <intmax_t N1, intmax_t D1>
      friend constexpr 
      pqs::conversion_factor<
         std::ratio<N1,D1>,
         pqs::unit_exp<N> 
      > operator * ( std::ratio<N1,D1>, exponent10_t )
      {
         return {};
      }

   };
#if defined  __cpp_inline_variables
   template <int N>
   inline constexpr auto exponent10 = exponent10_t<N>{};
#endif
}

void basic_quantity_test()
{
   pqs::basic_quantity<
      pqs::basic_unit<
         dummy_system,
         decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
         decltype( std::ratio<3,2>{} * pqs::exponent10<3>)
      >, double
   > x{20.0};
         
}