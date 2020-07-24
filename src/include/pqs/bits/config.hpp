#ifndef PQS_BITS_CONFIG_HPP_INCLUDED
#define PQS_BITS_CONFIG_HPP_INCLUDED

#include <pqs/bits/implicit_conversion_functions.hpp>
#include <pqs/types/charset.hpp>

/*
   if defined then a stream output shify function
   is added as a friend in the basic_quantity class
*/
#define PQS_BASIC_QUANTITY_FRIEND_OSTREAM_SUPPORT

namespace pqs{

      using real_type = double; // type used for floating point

      //conversion function
      // for dealing with narrowing etc
      using default_conversion = pqs::no_narrowing_conversion ;

      using default_charset = charset_utf8;
      
};

#endif // PQS_BITS_CONFIG_HPP_INCLUDED
