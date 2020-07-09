
#include <pqs/bits/base_quantities.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/si/unit.hpp>

#include <iostream>

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
            ( pqs::si::is_proper_si_unit<UL> ||
              pqs::si::is_proper_si_unit<UR> 
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
         using type = si::make_proper_si_unit<basic_type>;
      };
   }
   
   template <unit Lhs, unit Rhs>
   inline constexpr 
   auto operator / ( Lhs, Rhs)
   {
      return pqs::binary_op_t< Lhs, pqs::divides, Rhs>{};
   }
}   

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
         
      using R = binary_op_t<L, divides,T>;

      R constexpr r = L{} / T{};
       
      static_assert(pqs::is_basic_unit<R>);
   }

   void si_unit_div_test()
   {
      using L = si::proper_unit<
         decltype(abstract_length<> ),
         exponent10<-6>
      >;

      using T = basic_unit<
         si_measurement_system,
         decltype(abstract_time<> ),
         decltype(std::ratio<1>{} ^ exponent10<-2>{})
      >;
         
      using  R = binary_op_t<L, divides,T>;

      R constexpr r = L{} / T{};

      static_assert(is_basic_unit<R>);
      static_assert(si::is_proper_si_unit<R>);
   }

}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
    unit_div_test();
    si_unit_div_test();
}
