
/*
 @brief make std::chrono::duration a model of pqs::quantity and test it works
*/

#include <chrono>
#include <pqs/concepts/quantity.hpp>
#include <pqs/types/base_quantity/time.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs::impl{

  /** @brief fulfill quantity requirements for chrono duration
   * see https://github.com/kwikius/pqs/wiki/concept-quantity#requires
   */
   template < typename Rep,typename Period >
   struct get_unit_impl<std::chrono::duration<Rep, Period> >{

      // chrono Period is rational representing sec
      using cf = decltype(typename Period::type() ^ pqs::exponent10<0>());
      static auto constexpr cf_v = cf{};
      using cf_mux = typename cf::multiplier;

      static bool constexpr is_normative = (cf_mux::den == 1) && (cf_mux::num == 1);

      using measurement_system = pqs::si_measurement_system;
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
   template < typename  Rep,typename Period >
   struct get_numeric_type_impl<std::chrono::duration<Rep, Period> >{
      using type = Rep;
   };

   /** @brief  fulfill quantity requirements for chrono duration.
    *
    * declare that std::chrono::duration is a model of pqs::quantity
    */
   template< typename Rep, typename Period >
   inline constexpr bool is_quantity_impl<std::chrono::duration<Rep, Period> > = true;

}

namespace std::chrono{

   /** @brief  fulfill quantity requirements for chrono duration.
    *
    * we can define in std::chrono or globally if that is not acceptable
    */
   template< typename Rep, typename Period >
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

int main()
{
   std::cout << "PQS demo : make std::chrono duration a model of pqs::quantity\n\n";

   auto constexpr distance = 1.0q_m;
   auto constexpr time = std::chrono::microseconds{2000000};

   pqs::si::speed::m_per_s<> q1 = distance / time ;

   std::cout 
   << "distance = " <<  distance 
      //for simplicity  cast the chrono duration to some pqs::basic_quantity which has stream output
   << " and time = " << pqs::implicit_cast<si::time::ms<> >(time) 
   << " , so speed = " << q1 << '\n';
}

