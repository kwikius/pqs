
#include <pqs/systems/si/length.hpp>

/**
 * @brief demonstrating how conversion_factors relate
 * dimensionallt equivalent quantities
 * in same measurement system with different conversion_factors
 */
int main()
{
   std::cout << "PQS relation of conversion factors example\n";

   using namespace pqs;

   using Qb = si::length::m<>;
   using Q  = si::length::ft<>;

   static_assert( same_measurement_system< Q,Qb > );
   static_assert( evaluate<get_conversion_factor< Qb > >() == 1 );
   static_assert( evaluate<get_conversion_factor< Q > >() != 1 );

   constexpr dimensionless_quantity n = -12345.678;
   
   constexpr Q  q{n};
   constexpr Qb qB = q;

   static_assert( 
      get_numeric_value(qB) == 
         get_numeric_value(q) * evaluate<get_conversion_factor<Q> >() 
   );
}