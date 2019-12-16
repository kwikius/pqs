#ifndef PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
#define PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <ratio>
#include <pqs/meta/and.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/base_quantities/physical/length.hpp>

namespace pqs_exposition{

   namespace detail{
      struct base_quantity_exp_base{};

      template <typename T>
      struct is_base_quantity_exp : std::is_base_of<pqs_exposition::detail::base_quantity_exp_base,T>{};
   }

   template < int N, int D , typename BaseQuantity>
   struct base_quantity_exp : pqs_exposition::detail::base_quantity_exp_base{
      static_assert(pqs::is_base_quantity<BaseQuantity>::value,"Not a model of base_quantity");
      typedef BaseQuantity base_quantity;
      typedef typename std::ratio<N,D>::type ratio;
      typedef base_quantity_exp type;
   };

}

namespace pqs{

   namespace impl{

      template <  typename T>
      struct is_base_quantity_exp_impl<T,
         typename pqs::where_<pqs_exposition::detail::is_base_quantity_exp<T> >::type
      > : std::true_type{};

      

   } // impl

} // pqs


namespace pqs_exposition{

   template <int N, int D>
   struct exp_length_r : base_quantity_exp<N,D,pqs::physical::base_quantity_length>{
      typedef exp_length_r type;
   };

   template <int N>
   struct exp_length : base_quantity_exp<N,1,pqs::physical::base_quantity_length>{
      typedef exp_length type;
   };
}

//##############################################################################
#if 0

   namespace detail{

      struct base_quantity_exp_base_class{};

      enum class base_quantity_id_t : uint8_t {
         length,
         first_element = length,
         time,
         mass,
         temperature,
         current,
         substance,
         intensity,
         last_element = intensity
      };

      template <base_quantity_id_t ID, int N, int D>
      struct base_quantity_exp : base_quantity_exp_base_class{ 
         typedef typename std::ratio<N,D>::type ratio;
         static constexpr base_quantity_id_t base_quantity_id  = ID;
      };

  }
#endif 

 
// TODO customise in pqs impl namespace
#if 0
      template <typename T>
      struct is_base_quantity_exp : std::is_base_of<base_quantity_exp_base_class,T>{};

      // have same id but not necessarily same value
      template <typename TL, typename TR, typename = void>
      struct same_base_quantity_impl : std::false_type{};

      template <typename TL, typename TR>
      struct same_base_quantity_impl<TL,TR,
         typename std::enable_if<
            pqs::meta::and_<
               is_base_quantity_exp<TL>, 
               is_base_quantity_exp<TR>
            >::value
         >::type

      > : std::integral_constant< bool,(TL::base_quantity_id == TR::base_quantity_id)>{};

      template <typename TL, typename TR>
      struct same_base_quantity : same_base_quantity_impl<TL,TR>{};

  // } // detail
#endif

#if 0
namespace pqs_exposition{
   // interface
   // the dimension ratio interface when base dimension extent is not an integer
   // which is infrequent but allowed
   template <int N, int D > struct dim_length_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::length,N,D>{ };
   template <int N, int D > struct dim_time_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::time,N,D>{};
   template <int N, int D > struct dim_mass_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::mass,N,D>{};
   template <int N, int D > struct dim_temperature_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::temperature,N,D>{};
   template <int N, int D > struct dim_current_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::current,N,D>{};
   template <int N, int D > struct dim_substance_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::substance,N,D>{};
   template <int N, int D > struct dim_intensity_ratio : detail::base_quantity_exp<detail::base_quantity_id_t::intensity,N,D>{};

   // interface
   // the dimension ratio interface for the usual case of an integer base_deminsion extent
   template <int N> struct dim_length : dim_length_ratio<N,1>{};
   template <int N> struct dim_time : dim_time_ratio<N,1>{};
   template <int N> struct dim_mass : dim_mass_ratio<N,1>{};
   template <int N> struct dim_temperature : dim_temperature_ratio<N,1>{};
   template <int N> struct dim_current : dim_current_ratio<N,1>{};
   template <int N> struct dim_substance : dim_substance_ratio<N,1>{};
   template <int N> struct dim_intensity : dim_intensity_ratio<N,1>{};

   namespace detail {

      // use the id to generate the most derived base_quantity_exp
      template <base_quantity_id_t ID, typename Ratio> 
      struct make_base_quantity_ratio_impl;

      // call the impl to reduce the ratio
      template < base_quantity_id_t ID , typename Ratio> 
      struct make_base_quantity_ratio: make_base_quantity_ratio_impl<ID,typename Ratio::type>{};

      // implement for the usual suspects ...

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::length, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_length<Ratio::num>,pqs_exposition::dim_length_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::time, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_time<Ratio::num>,pqs_exposition::dim_time_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::mass, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_mass<Ratio::num>,pqs_exposition::dim_mass_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::temperature, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_temperature<Ratio::num>,pqs_exposition::dim_temperature_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::current, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_current<Ratio::num>,pqs_exposition::dim_current_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::substance, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_substance<Ratio::num>,pqs_exposition::dim_substance_ratio<Ratio::num,Ratio::den>
      >{};

      template <typename Ratio> 
      struct make_base_quantity_ratio_impl<base_quantity_id_t::intensity, Ratio> 
      : std::conditional< 
         Ratio::den == 1, pqs_exposition::dim_intensity<Ratio::num>,pqs_exposition::dim_intensity_ratio<Ratio::num,Ratio::den>
      >{};

      //  ---operations on base dimensions -----------------------------------
      // add,subtract, negate, multiply divide by ratio, compare
      template <typename BdrL, typename BdrR>
      struct add_base_quantity_ratio : make_base_quantity_ratio<
         BdrL::base_quantity_id,std::ratio_add<typename BdrL::ratio,typename BdrR::ratio>
      > { 
         static_assert(BdrL::base_quantity_id == BdrR::base_quantity_id, "incompatible base dimension ratios for +");
      };

      template <typename BdrL, typename BdrR>
      struct subtract_base_quantity_ratio : make_base_quantity_ratio<
         BdrL::base_quantity_id,std::ratio_subtract<typename BdrL::ratio,typename BdrR::ratio>
      > { 
         static_assert(BdrL::base_quantity_id == BdrR::base_quantity_id, "incompatible base dimension ratios for -");
      };

      template <typename Bdr>
      struct negate_base_quantity_ratio : make_base_quantity_ratio< 
         Bdr::base_quantity_id, std::ratio_subtract<std::ratio<0,1>,typename Bdr::ratio>
      >{};

      template <typename Bdr, typename Multiplier>
      struct multiply_base_quantity_ratio : make_base_quantity_ratio<
         Bdr::base_quantity_id,std::ratio_multiply<typename Bdr::ratio,Multiplier>
      >{};

      template <typename Bdr, typename Divisor>
      struct divide_base_quantity_ratio : make_base_quantity_ratio<
         Bdr::base_quantity_id,std::ratio_divide<typename Bdr::ratio,Divisor>
      >{};

      template <typename BdrL, typename BdrR>
      struct base_quantity_ratio_equal_to : std::ratio_equal<typename BdrL::ratio,typename BdrR::ratio> {};

      template <typename BdrL, typename BdrR>
      struct base_quantity_ratio_not_equal_to: std::ratio_not_equal<typename BdrL::ratio,typename BdrR::ratio> {};

      template <typename Bdr>
      struct base_quantity_is_zero : std::ratio_equal<typename Bdr::ratio, std::ratio<0> >{};

   }//detail

} // pqs_exposition
#endif
#endif // PQS_EXPOSITION_BASE_QUANTITY_EXP_HPP_INCLUDED
