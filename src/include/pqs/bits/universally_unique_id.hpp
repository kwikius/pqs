#ifndef PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
#define PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED

#include <cstdint>

namespace pqs{

   template <uint16_t... Id>
   struct universally_unique_id {
      static constexpr uint16_t elements[] = {Id...};
      static constexpr std::size_t num_elements = sizeof...(Id);
   }

   template <uint16_t... Id>
   constexpr uint16_t universally_unique_id<Id... >::elements[] ;

}

#endif // PQS_UUID_H_INCLUDEDPQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
