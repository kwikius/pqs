#ifndef PQS_IMPLIT_CONVERSION_FUNCTIONS_HPP_INCLUDED
#define PQS_IMPLIT_CONVERSION_FUNCTIONS_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/where.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/meta/is_narrowing_conversion.hpp>

namespace pqs{

   template <typename From, typename T>
   struct invalid_conversion{};

   struct no_conversion{

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         std::is_same<Tout,Tin>,
         Tout
       >::type
       apply( Tin const & in)
       { return in;}

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::not_<std::is_same<Tout,Tin> >,
         pqs::invalid_conversion<Tin,Tout>
       >::type
       apply( Tin const & in)
       { return pqs::invalid_conversion<Tin,Tout>{};}
       
   };

   struct no_narrowing_conversion{


       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::not_< pqs::meta::is_narrowing_conversion<Tin,Tout> >,
         Tout
       >::type
       apply( Tin const & in)
       { return static_cast<Tout>(in);}

       template <typename Tout, typename Tin>
       constexpr static 
       typename pqs::where_<
         pqs::meta::is_narrowing_conversion<Tin,Tout>,
         pqs::invalid_conversion<Tin,Tout>
       >::type
       apply( Tin const & in)
       { return pqs::invalid_conversion<Tin,Tout>{};}
   };

}

#endif // PQS_IMPLIT_CONVERSION_FUNCTIONS_HPP_INCLUDED
