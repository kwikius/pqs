#ifndef PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/bits/unary_op.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/bits/universally_unique_id.hpp>

#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/mass.hpp>
#include <pqs/base_quantity/temperature.hpp>
#include <pqs/base_quantity/current.hpp>
#include <pqs/base_quantity/intensity.hpp>
#include <pqs/base_quantity/substance.hpp>

/*
 base quantities are primitive members of a quantity universe
*/

namespace pqs_exposition{

   namespace detail{
      struct base_quantity_exp_base{};

      template <typename T>
      struct is_base_quantity_exp 
      : std::is_base_of<pqs_exposition::detail::base_quantity_exp_base,T>{};
   }

   template <typename BaseQuantity, int N, int D =1>
   struct exp : pqs_exposition::detail::base_quantity_exp_base{
      static_assert(pqs::is_base_quantity<BaseQuantity>::value,"Not a model of base_quantity");
      typedef BaseQuantity base_quantity;
      typedef typename std::ratio<N,D>::type ratio;
      typedef exp type;
   };

}

namespace pqs{

   // make pqs_exposition exp model of pqs::base_quantity_exp
   namespace impl{

      template <  typename T>
      struct is_base_quantity_exp_impl<
         T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > : std::true_type{};

      template <typename T>
      struct get_base_quantity_impl<
         T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > : T::base_quantity {};

      template <typename T>
      struct get_exponent_impl<
         T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > {
         typedef typename T::ratio type;
      };

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::time_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_time,Ratio::type::num, Ratio::type::den
//      >{};

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::length_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_length,Ratio::type::num, Ratio::type::den
//      >{};

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::mass_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_mass,Ratio::type::num, Ratio::type::den
//      >{};
//
//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::temperature_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_temperature,Ratio::type::num, Ratio::type::den
//      >{};

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::current_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_current,Ratio::type::num, Ratio::type::den
//      >{};

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::substance_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_substance,Ratio::type::num, Ratio::type::den
//      >{};

//      template <typename Ratio>
//      struct make_base_quantity_exp_impl<pqs::newtonian_universe::intensity_uuid,Ratio>
//      : pqs_exposition::exp<
//          pqs::base_intensity,Ratio::type::num, Ratio::type::den
//      >{};

   } // impl

} // pqs

#endif // PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
