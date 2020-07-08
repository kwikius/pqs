
#include <pqs/bits/base_quantities.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/si/unit.hpp>

#include <iostream>

namespace pqs{

   namespace impl{

      template <unit Lhs, unit Rhs>
         requires 
            std::is_same_v<
               get_measurement_system<Lhs>,
               get_measurement_system<Rhs>
            >
      struct binary_op_impl< Lhs, pqs::divides, Rhs> {
          using SmL = get_measurement_system<Lhs>;
          using DL = get_dimension<Lhs>; 
          using CfL = get_conversion_factor<Lhs>;

          using SmR = get_measurement_system<Rhs>;
          using DR = get_dimension<Rhs>; 
          using CfR = get_conversion_factor<Rhs>;

          static_assert(std::is_same_v<SmL,SmR>);

          using D = std::remove_cvref_t<decltype( DL{} / DR{})>;
          static_assert( ! std::is_same_v<D,dimensionless>);
          using Cf = pqs::binary_op_t<CfL,pqs::divides,CfR>;

          using type = basic_unit<SmL,D,Cf>;
      };

      /*
         if one or other is proper si unit
         then convert result to proper si unit.
         N.b Take care to make the inputs
         proper too in runtime op
      */
      template <unit Lhs, unit Rhs>
         requires 
            std::is_same_v<
               get_measurement_system<Lhs>,
               get_measurement_system<Rhs>
            > && (
               pqs::si::is_proper_si_unit<Lhs> ||
               pqs::si::is_proper_si_unit<Rhs> 
            )
      struct binary_op_impl< Lhs, pqs::divides, Rhs> {
          using SmL = get_measurement_system<Lhs>;
          using DL = get_dimension<Lhs>; 
          using CfL = get_conversion_factor<Lhs>;

          using SmR = get_measurement_system<Rhs>;
          using DR = get_dimension<Rhs>; 
          using CfR = get_conversion_factor<Rhs>;

          using D = std::remove_cvref_t<decltype( DL{} / DR{})>;
          static_assert( ! std::is_same_v<D,dimensionless>);
          using Cf = pqs::binary_op_t<CfL,pqs::divides,CfR>;
          using basic_type = basic_unit<SmL,D,Cf>;
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
         
      using  R = binary_op_t<L, divides,T>;

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
