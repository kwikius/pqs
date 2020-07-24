
#include <time.h>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/imperial/length.hpp>
#include <pqs/systems/imperial/time.hpp>

#include <iostream>

#if 0
namespace pqs{

   namespace impl{

      template <unit UL, unit UR>
         requires 
            same_measurement_system<UL,UR> && 
            dimension< 
               binary_op_t<
                  get_dimension<UL>,
                  pqs::divides,
                  get_dimension<UR>
               >
            >
      struct binary_op_impl< UL, pqs::divides, UR> {
 
         using measurement_system = 
            get_measurement_system<UL>;
         using conversion_factor = 
            pqs::binary_op_t<
               get_conversion_factor<UL>,
               pqs::divides,
               get_conversion_factor<UR>
            >;
         using dimension = 
            pqs::binary_op_t<
               get_dimension<UL>,
               pqs::divides,
               get_dimension<UR>
            >;
         using type =
            pqs::basic_unit<
               measurement_system,
               dimension,
               conversion_factor
            >;
      };

      /*
         refinement for SI
         if one or other is proper si unit
         then convert result to proper si unit.
         N.b Take care to make the inputs
         proper too in runtime op before calc
      */
      template <unit UL, unit UR>
         requires 
            same_measurement_system<UL,UR> && 
            dimension< 
               binary_op_t<
                  get_dimension<UL>,
                  pqs::divides,
                  get_dimension<UR>
               >
            > &&
            ( pqs::si::is_normative_unit<UL> ||
              pqs::si::is_normative_unit<UR> 
            )
      struct binary_op_impl< UL, pqs::divides, UR> {
         using conversion_factor = 
            pqs::binary_op_t<
               get_conversion_factor<UL>,
               pqs::divides,
               get_conversion_factor<UR>
            >;
         using dimension = 
            pqs::binary_op_t<
               get_dimension<UL>,
               pqs::divides,
               get_dimension<UR>
            >;
         using basic_type =
            pqs::basic_unit<
               pqs::si_measurement_system,
               dimension,
               conversion_factor
            >;
         using type = si::make_normative_unit<basic_type>;
      };
   }
   
   template <unit Lhs, unit Rhs>
   inline constexpr 
   auto operator / ( Lhs, Rhs)
   {
      return pqs::binary_op_t< Lhs, pqs::divides, Rhs>{};
   }
}   
#endif

using namespace pqs;

namespace {

   void unit_div_test()
   {
      using L = basic_unit<
         si_measurement_system,
         decltype(abstract_length<> ),
         decltype(std::ratio<1>{} ^ exponent10<0>{})
      >;

      using T = basic_unit<
         si_measurement_system,
         decltype(abstract_time<> ),
         decltype(std::ratio<1>{} ^ exponent10<0>{})
      >;
         
    //  using R = binary_op_t<L, divides,T>;

      auto constexpr r = L{} / T{};
       
      static_assert(pqs::is_basic_unit<decltype(r)>);
   }

   void si_unit_div_test()
   {
      using L = si::normative_unit<
         decltype(abstract_length<> ),
         exponent10<-6>
      >;

      // has to be assumed non-normative?
      using T = basic_unit<
         si_measurement_system,
         decltype(abstract_time<> ),
         decltype(std::ratio<1>{} ^ exponent10<-2>{})
      >;
         
     // using R = binary_op_t<L, divides,T>;

      auto constexpr r = L{} / T{};

      static_assert(is_basic_unit<decltype(r)>);

      // should fail unless both normative units?
      static_assert(not si::is_normative_unit<decltype(r)>);
   }

}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void unit_binary_op_test()
#endif
{
    unit_div_test();
    si_unit_div_test();
}
