
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

} // pqs::impl

namespace std::chrono{

   /** @brief  fulfill quantity requirements for chrono duration.
    *
    * we can define in std::chrono or globally if that is not acceptable
    */
   template<pqs::dimensionless_quantity Rep, typename Period >
       requires pqs::is_ratio<Period>
   inline constexpr Rep get_numeric_value(std::chrono::duration<Rep, Period> const & q)
   {
      return q.count();
   }
}

// extra feature - Add support for converting a suitable quantity to a chrono duration
namespace pqs::impl::detail{

   /**
   * @brief ll convert a conversion factor into a std::ratio if possible
   **/
   template <typename Mux, int64_t Exp>
   struct expand_mux_exp{

      using type = typename pqs::meta::eval_if_t<
         std::bool_constant<(Exp < 0)>,
            expand_mux_exp< 
               std::ratio_divide<Mux,std::ratio<10> >,
               Exp + 1 
            >,
         std::bool_constant<(Exp > 0)>,
            expand_mux_exp< 
               std::ratio_multiply<Mux,std::ratio<10> >,
               Exp - 1 
            >,
            Mux
      >;    
   };

}//pqs::impl::detail

namespace pqs::impl{

   /**
   * @brief convert a conversion factor into a std::ratio if possible - impl
   **/
   template <typename CF> 
   struct conversion_factor_as_ratio_impl{
       using multiplier = typename CF::multiplier ; // std::ratio
       using exponent =  typename CF::exponent::ratio; // ratio
       // Only proceed if exponent is an integer 
       static_assert(exponent::den == 1);

       using type = typename pqs::impl::detail::expand_mux_exp<multiplier, exponent::num>::type;
   };

} // pqs::impl

namespace pqs{

      /**
   * @brief convert a conversion factor into a std::ratio if possible - interface
   **/

    template <typename CF> 
    using conversion_factor_as_ratio = typename impl::conversion_factor_as_ratio_impl<CF>::type;
    
    /**
      @brief overload duration_cast to cast a quantity to a chrono::duration
    */
    template <typename D, quantity Q>
       requires dimensionally_equivalent<get_dimension<Q>, pqs::abstract_time_t>
    inline auto constexpr duration_cast(Q const & q)
    {
        // an equivalent unit but as a chrono duration
        using equivalent_type = std::chrono::duration<
            get_numeric_type<Q>,
            conversion_factor_as_ratio<get_conversion_factor<Q> > 
        >;
        //Its easier from here... use the chrono durations own casting mechanisms now
        return duration_cast<D>(equivalent_type(get_numeric_value(q)));
    }
}

//------------------------------------------

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
   // (See end of example for casting to the default)
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

   // How does duration as quantity concept play with existing duration operators ?
   // No conflict here since chrono is in a different namespace
   
   auto constexpr d1 = time / 2;  // a chrono::duration
   auto constexpr d2 = time + time; // a chrono::duration

   auto constexpr time1 = 1.0q_s;
   // mixed addition finds the operators in quantity namespace
   auto constexpr q3 = time + time1;  // a pqs::time

  // provide overloaded duration_cast for converting to a chrono type
  auto constexpr d3 = duration_cast<std::chrono::milliseconds>(q3);

  std::cout <<  q3 << " == " <<  d3.count() << " chrono::duration::milliseconds\n";
   
}
