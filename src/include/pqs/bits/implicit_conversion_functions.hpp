#ifndef PQS_IMPLICIT_CONVERSION_FUNCTIONS_HPP_INCLUDED
#define PQS_IMPLICIT_CONVERSION_FUNCTIONS_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/bits/meta/not.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/bits/meta/is_narrowing_conversion.hpp>
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
          requires ! meta::is_narrowing_conversion<Tin,Tout>
       constexpr static 
       auto apply( Tin const & v)
       { return static_cast<Tout>(v);}

       template <typename Tout, typename Tin>
         requires  meta::is_narrowing_conversion<Tin,Tout>
       constexpr static 
       auto apply( Tin const & v)
       { return Tout{v};}
   };

   struct no_conversion{

       template <typename Tout, typename Tin>
         requires std::is_same_v<Tout,Tin>
       constexpr static 
       auto apply( Tin const & v)
       { return v;}

       template <typename Tout, typename Tin>
         requires ! std::is_same_v<Tout,Tin>
       constexpr static 
       auto apply( Tin const & v)
       { return pqs::invalid_conversion<Tin,Tout,no_conversion>{};}
       
   };

   struct no_narrowing_conversion{

       template <typename Tout, typename Tin>
         requires ! meta::is_narrowing_conversion<Tin,Tout>
       constexpr static 
       auto apply( Tin const & v)
       { return static_cast<Tout>(v);}

       template <typename Tout, typename Tin>
         requires meta::is_narrowing_conversion<Tin,Tout>
       constexpr static 
       auto apply( Tin const & v)
       { return pqs::invalid_conversion<Tin,Tout,no_narrowing_conversion>{};}
   };

   struct range_checked_conversion{

      template <typename Tout, typename Tin>
         requires ! meta::is_narrowing_conversion<Tin,Tout>
      constexpr static 
      auto apply( Tin const & v)
      { return static_cast<Tout>(v);}

#if ! defined PQS_NO_EXCEPTIONS
      template <typename Tout, typename Tin>
         requires meta::is_narrowing_conversion<Tin,Tout>
      constexpr static 
      auto apply( Tin const & v)
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
        requires ! meta::is_narrowing_conversion<Tin,Tout>
      constexpr static 
      auto apply( Tin const & v)
      { return static_cast<Tout>(v);}

      template <typename Tout, typename Tin>
         requires meta::is_narrowing_conversion<Tin,Tout>
      constexpr static 
      auto apply( Tin const & v)
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
