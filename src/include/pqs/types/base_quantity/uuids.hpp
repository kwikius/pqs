#ifndef PQS_BASE_UUIDS_HPP_INCLUDED
#define PQS_BASE_UUIDS_HPP_INCLUDED

#include <pqs/types/uuid.hpp>

namespace pqs{ 

/*
These correspond to the 'short form' ids in the bluetooth specification
https://www.bluetooth.com/specifications/assigned-numbers/units/
*/
   namespace newtonian_universe{

      // where U is a uuid
      // require model of pqs::meta::identity_function<U>
      struct length_uuid      : universally_unique_id<0x2701>{typedef length_uuid type;};
      struct mass_uuid        : universally_unique_id<0x2702>{typedef mass_uuid type;};
      struct time_uuid        : universally_unique_id<0x2703>{typedef time_uuid type;};
      struct current_uuid     : universally_unique_id<0x2704>{typedef current_uuid type;};
      struct temperature_uuid : universally_unique_id<0x2705>{typedef temperature_uuid type;};
      struct substance_uuid   : universally_unique_id<0x2706>{typedef substance_uuid type;};
      struct intensity_uuid   : universally_unique_id<0x2707>{typedef intensity_uuid type;};
   }

}

#endif // PQS_BASE_UUIDS_HPP_INCLUDED
