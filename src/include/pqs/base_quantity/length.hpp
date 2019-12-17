#ifndef PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

   struct base_length : pqs::base_quantity_of<pqs::length_uuid>{
      // the member type makes base_length a model of meta_identity_function
      // This provides somewhat more concise error messages
      typedef base_length type;
   };
}

#endif // PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
