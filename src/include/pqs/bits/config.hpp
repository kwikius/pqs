#ifndef PQS_BITS_CONFIG_HPP_INCLUDED
#define PQS_BITS_CONFIG_HPP_INCLUDED

#include <pqs/bits/implicit_conversion_functions.hpp>

namespace pqs{

      typedef double real_type; // type used for floating point

      //conversion function
      // for dealing with narrowing etc
      typedef pqs::no_narrowing_conversion default_conversion;
      
};

#endif // PQS_BITS_CONFIG_HPP_INCLUDED
