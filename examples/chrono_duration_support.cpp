
/*
 @brief make std::chrono::duration a model of pqs::quantity and test it works
*/

#include <chrono>
#include <pqs/concepts/quantity.hpp>
#include <pqs/types/base_quantity/time.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs::impl{

  /** @brief fulfill quantity requirements for chrono duration
   *
   * For the requirements to make a type a model of quantity 
   * see https://github.com/kwikius/pqs/wiki/concept-quantity#requires
   *
   * Here we chose to make the std::chrono::duration a model of a quantity in the si system.
   */
   template < dimensionless_quantity Rep,typename Period >
     requires pqs::is_ratio<Period>
   struct get_unit_impl<std::chrono::duration<Rep, Period> >{

      // std::chrono::duration Period is a std::ratio<...> rational number representing
      // conversion of the numeric value of its member count() to seconds.
      // Use the convenience operator to create a conversion_factor from the Period 
      // for compatibility with pqs::unit concept.
      static auto constexpr cf_v = typename Period::type() ^ pqs::exponent10<0>();
      using cf = decltype(cf_v);
      using cf_mux = typename cf::multiplier;

      // A conversion_factor multiplier of 1 signifies a normative si quantity ...
      static bool constexpr is_normative = (cf_mux::den == 1) && (cf_mux::num == 1);

      // choose a normative_unit if possible else a unit_conversion
      using type = std::conditional<
         is_normative,
         pqs::si::normative_unit<
            pqs::abstract_time_t,
            typename cf::exponent
         >,
         pqs::si::unit_conversion<
            pqs::abstract_time_t,
            cf_v
         >
      >::type;
   };

   /** @brief fulfill quantity requirements for chrono duration 
   */
   template <dimensionless_quantity Rep,typename Period >
      requires pqs::is_ratio<Period>
   struct get_numeric_type_impl<std::chrono::duration<Rep, Period> >{
      using type = Rep;
   };

   /** @brief  fulfill quantity requirements for chrono duration.
    *
    * declare that std::chrono::duration is a model of pqs::quantity
    */
   template<dimensionless_quantity Rep, typename Period>
      requires pqs::is_ratio<Period>
   inline constexpr bool is_quantity_impl<std::chrono::duration<Rep, Period> > = true;

}

namespace std::chrono{

   /** @brief  fulfill quantity requirements for chrono duration.
    *
    * we can define in std::chrono or globally if that is not acceptable
    */
   template< pqs::dimensionless_quantity Rep, typename Period >
       requires pqs::is_ratio<Period>
   inline constexpr Rep get_numeric_value(std::chrono::duration<Rep, Period> const & q)
   {
      return q.count();
   }
}

#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/speed.hpp>

using namespace pqs;
using namespace pqs::si::literals;
using namespace std::literals::chrono_literals;

int main()
{
   std::cout << "PQS demo : make std::chrono duration a model of pqs::quantity\n\n";

   auto constexpr distance = 1.0q_m;
   auto constexpr time = 2000000.0us ; //std::chrono::microseconds{2000000};

   // chrono::duration literals return a type with a long double rep type
   // pqs quantity disallows implicit conversion of the numeric_value
   // from long double to its default double numeric type as a narrowing conversion,
   // so for simplicity we use a long double quantity value_type here.
   // (See end of example for casting to the defualt)
   pqs::si::speed::m_per_s<long double> q1 = distance / time ;

   std::cout 
   << "distance = " <<  distance 
      //for simplicity  cast the chrono duration to some pqs::basic_quantity which has stream output
   << " and time = " << pqs::implicit_cast<si::time::ms<long double> >(time) 
   << " , so speed = " << q1 << '\n';

   // to use the default double value type we need to use explicit_cast
   pqs::si::time::ns<> constexpr t1 = pqs::explicit_cast<double>(1000000.0us);

   auto q2 = distance / t1;

   q1 = q2;  // ok to cast value from double to long double as not narrowing

   q2 = pqs::explicit_cast<double>(q1); // but requires a cast the other way

   std::cout << "\nnow speed = " << q1 <<'\n';
   
}

