#ifndef PQS_BASE_UUIDS_HPP_INCLUDED
#define PQS_BASE_UUIDS_HPP_INCLUDED

#include <pqs/bits/universally_unique_id.hpp>

namespace pqs{ namespace physical{

/*
These correspond to the 'short form' ids in the bluetooth specification
https://www.bluetooth.com/specifications/assigned-numbers/units/
*/

   struct length_uuid      : universally_unique_id<0x2701>{};
   struct mass_uuid        : universally_unique_id<0x2702>{};
   struct time_uuid        : universally_unique_id<0x2703>{};
   struct current_uuid     : universally_unique_id<0x2704>{};
   struct temperature_uuid : universally_unique_id<0x2705>{};
   struct substance_uuid   : universally_unique_id<0x2706>{};
   struct intensity_uuid   : universally_unique_id<0x2707>{};

}}

#endif // PQS_BASE_UUIDS_HPP_INCLUDED
