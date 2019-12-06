#ifndef STD_UNITS_SI_UNITS_HPP_INCLUDED
#define STD_UNITS_SI_UNITS_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <ratio>

namespace std{

   template <typename U, typename V = double>
   class quantity{};

   template <typename ...D>
   struct dimension;

   namespace si{

      namespace detail{

         struct base_dimension_ratio_base_class{};

         enum class base_dimension_id_t : uint8_t {
             undefined,
             length,
             time,
             mass,
             temperature,
             current,
             substance,
             intensity
         };

         template <base_dimension_id_t ID, int N, int D>
         struct base_dimension_ratio : base_dimension_ratio_base_class{ 
            typedef typename std::ratio<N,D>::type ratio;
            static constexpr base_dimension_id_t base_dimension_id  = ID;
         };

         template <typename T>
         struct is_base_dimension_ratio : std::is_base_of<base_dimension_ratio_base_class,T>{};

      }

      // interface
      // the dimension ratio interface when base dimension extent is not an integer
      // which is infrequent but allowed
      template <int N, int D > struct dim_length_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::length,N,D>{ };
      template <int N, int D > struct dim_time_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::time,N,D>{};
      template <int N, int D > struct dim_mass_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::mass,N,D>{};
      template <int N, int D > struct dim_temperature_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::temperature,N,D>{};
      template <int N, int D > struct dim_current_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::current,N,D>{};
      template <int N, int D > struct dim_substance_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::substance,N,D>{};
      template <int N, int D > struct dim_intensity_ratio : detail::base_dimension_ratio<detail::base_dimension_id_t::intensity,N,D>{};

      // the dimension ratio interface for the usual case of an integer base_deminsion extent
      template <int N=1> struct dim_length : dim_length_ratio<N,1>{};
      template <int N=1> struct dim_time : dim_time_ratio<N,1>{};
      template <int N=1> struct dim_mass : dim_mass_ratio<N,1>{};
      template <int N=1> struct dim_temperature : dim_temperature_ratio<N,1>{};
      template <int N=1> struct dim_current : dim_current_ratio<N,1>{};
      template <int N=1> struct dim_substance : dim_substance_ratio<N,1>{};
      template <int N=1> struct dim_intensity : dim_intensity_ratio<N,1>{};

      namespace detail {

         // use the id to generate the most derived base_dimension_ratio
         template <base_dimension_id_t ID, typename Ratio> 
         struct make_base_dimension_ratio_impl;

        // call the impl to reduce the ratio
         template < base_dimension_id_t ID , typename Ratio> 
         struct make_base_dimension_ratio: make_base_dimension_ratio_impl<ID,typename Ratio::type>{};

         // implement for the usual suspects ...

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::length, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_length<Ratio::num>,std::si::dim_length_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::time, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_time<Ratio::num>,std::si::dim_time_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::mass, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_mass<Ratio::num>,std::si::dim_mass_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::temperature, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_temperature<Ratio::num>,std::si::dim_temperature_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::current, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_current<Ratio::num>,std::si::dim_current_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::substance, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_substance<Ratio::num>,std::si::dim_substance_ratio<Ratio::num,Ratio::den>
          >{};

         template <typename Ratio> 
         struct make_base_dimension_ratio_impl<base_dimension_id_t::intensity, Ratio> 
         : std::conditional< 
            Ratio::den == 1, std::si::dim_intensity<Ratio::num>,std::si::dim_intensity_ratio<Ratio::num,Ratio::den>
          >{};

          //  ---operations -----------------------------------
          // add,subtract, negate, multiply divide by ratio
          // compare
         template <typename BdrL, typename BdrR>
         struct add_base_dimension_ratio : make_base_dimension_ratio<
               BdrL::base_dimension_id,std::ratio_add<typename BdrL::ratio,typename BdrR::ratio>
         > { 
            static_assert(BdrL::base_dimension_id == BdrR::base_dimension_id, "incompatible base dimension ratios for +");
         };

         template <typename BdrL, typename BdrR>
         struct subtract_base_dimension_ratio : make_base_dimension_ratio<
             BdrL::base_dimension_id,std::ratio_subtract<typename BdrL::ratio,typename BdrR::ratio>
         > { 
              static_assert(BdrL::base_dimension_id == BdrR::base_dimension_id, "incompatible base dimension ratios for -");
         };

         template <typename Bdr>
         struct negate_base_dimension_ratio : make_base_dimension_ratio< 
            Bdr::base_dimension_id, std::ratio_subtract<std::ratio<0,1>,typename Bdr::ratio>
         >{};

         template <typename Bdr, typename Multiplier>
         struct multiply_base_dimension_ratio : make_base_dimension_ratio<
               Bdr::base_dimension_id,std::ratio_multiply<typename Bdr::ratio,Multiplier>
         >{};

         template <typename Bdr, typename Divisor>
         struct divide_base_dimension_ratio : make_base_dimension_ratio<
               Bdr::base_dimension_id,std::ratio_divide<typename Bdr::ratio,Divisor>
         >{};

         template <typename BdrL, typename BdrR>
         struct base_dimension_ratio_equal_to : std::ratio_equal<typename BdrL::ratio,typename BdrR::ratio> {};
        
         template <typename BdrL, typename BdrR>
         struct base_dimension_ratio_not_equal_to: std::ratio_not_equal<typename BdrL::ratio,typename BdrR::ratio> {};
      }

      //interface
      template <typename Dim, int ExpN , int ExpD >
      struct unit_ratio{};
      // derive named si_units from here
      template <typename Dim, int ExpN> 
      struct unit : unit_ratio<Dim, ExpN,1>{};

      // derive non_si_units from here
      template <typename SiUnit, int MuxExp, int MuxD>
      struct unit_conversion{};

}} // std::of_si

// si_std definition namespace 
namespace std{ namespace si{ namespace length_unit{

   struct mm : si::unit< 
      std::dimension<std::si::dim_length<> > 
      ,-3
   >{};

   struct ft : si::unit_conversion< 
      si::unit< 
         std::dimension<std::si::dim_length<1> >
         ,-1
      >
      ,381,125
    >{};

}}} // std::si::length_unit

// si quantities length definition namespace 
namespace std{ namespace si { namespace length{

   template <typename ValueType = double>
   using mm = quantity<length_unit::mm,ValueType>;

   template <typename ValueType = double>
   using ft = quantity<length_unit::ft,ValueType>;

}}} // std::si::length


#endif // STD_UNITS_SI_UNITS_HPP_INCLUDED
