#ifndef PQS_IMPLICIT_CONVERSION_FUNCTIONS_HPP_INCLUDED
#define PQS_IMPLICIT_CONVERSION_FUNCTIONS_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/meta/is_narrowing_conversion.hpp>
#include <pqs/bits/ll_config.hpp>
#include <pqs/bits/constrain.hpp>
#include <limits>
#if ! defined PQS_NO_EXCEPTIONS
#include <stdexcept>
#endif

namespace pqs{

   template <typename From, typename T, typename F>
   struct invalid_conversion{};

   struct warn_narrowing_conversion{

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::not_< pqs::meta::is_narrowing_conversion_legacy<Tin,Tout> >,
         Tout
       >::type
       apply( Tin const & v)
       { return static_cast<Tout>(v);}

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::is_narrowing_conversion_legacy<Tin,Tout>,
         Tout
       >::type
       apply( Tin const & v)
       { return Tout{v};}
   };

   struct no_conversion{

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         std::is_same<Tout,Tin>,
         Tout
       >::type
       apply( Tin const & v)
       { return v;}

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::not_<std::is_same<Tout,Tin> >,
         pqs::invalid_conversion<Tin,Tout,no_conversion>
       >::type
       apply( Tin const & v)
       { return pqs::invalid_conversion<Tin,Tout,no_conversion>{};}
       
   };

   struct no_narrowing_conversion{


       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::not_< pqs::meta::is_narrowing_conversion_legacy<Tin,Tout> >,
         Tout
       >::type
       apply( Tin const & v)
       { return static_cast<Tout>(v);}

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::is_narrowing_conversion_legacy<Tin,Tout>,
         pqs::invalid_conversion<Tin,Tout,no_narrowing_conversion>
       >::type
       apply( Tin const & v)
       { return pqs::invalid_conversion<Tin,Tout,no_narrowing_conversion>{};}
   };

   struct range_checked_conversion{

      template <typename Tout, typename Tin>
      constexpr static 
      typename pqs::where_<
      pqs::meta::not_< pqs::meta::is_narrowing_conversion_legacy<Tin,Tout> >,
      Tout
      >::type
      apply( Tin const & v)
      { return static_cast<Tout>(v);}

#if ! defined PQS_NO_EXCEPTIONS
      template <typename Tout, typename Tin>
      constexpr static 
      typename pqs::where_<
      pqs::meta::is_narrowing_conversion_legacy<Tin,Tout>,
      Tout
      >::type
      apply( Tin const & v)
      { 

         if ( ( v >= static_cast<Tin>(std::numeric_limits<Tout>::lowest()))
         && ( v <= static_cast<Tin>(std::numeric_limits<Tout>::max()) ) ){
            return static_cast<Tout>(v);
         }else{
            if (  v < static_cast<Tin>(std::numeric_limits<Tout>::lowest()) ){
               throw std::underflow_error("underflow in range_checked_conversion");
            }else{
               if ( v > static_cast<Tin>(std::numeric_limits<Tout>::max())){
                  throw std::overflow_error("overflow in range_checked_conversion");
               }else{
                  throw std::logic_error("unknown error in range checked conversion");
               }
            }
         }
      }
#endif

   };

   struct saturating_conversion{

      template <typename Tout, typename Tin>
      constexpr static 
      typename pqs::where_<
         pqs::meta::not_< pqs::meta::is_narrowing_conversion_legacy<Tin,Tout> >,
         Tout
      >::type
      apply( Tin const & v)
      { return static_cast<Tout>(v);}

      template <typename Tout, typename Tin>
      constexpr static 
      typename pqs::where_<
         pqs::meta::is_narrowing_conversion_legacy<Tin,Tout>,
         Tout
      >::type
      apply( Tin const & v)
      { 
         return static_cast<Tout>(
            pqs::constrain(v, 
               static_cast<Tin>(std::numeric_limits<Tout>::lowest()),
               static_cast<Tin>(std::numeric_limits<Tout>::max())
            )
         );
      }
   };
}

#endif // PQS_IMPLICIT_CONVERSION_FUNCTIONS_HPP_INCLUDED
