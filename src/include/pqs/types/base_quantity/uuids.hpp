#ifndef PQS_BASE_UUIDS_HPP_INCLUDED
#define PQS_BASE_UUIDS_HPP_INCLUDED

#include <pqs/types/uuid.hpp>

namespace pqs::newtonian_universe{

  /**
   * @defgroup newtonian_universe_uuids Newtonian Universe UUIDS
   * @brief These uuids correspond to the 'short form' ids in the bluetooth specification .
   * https://www.bluetooth.com/specifications/assigned-numbers/units/  
   * @{
   */
   struct length_uuid      : uuid<0x2701>{typedef length_uuid type;};
   struct mass_uuid        : uuid<0x2702>{typedef mass_uuid type;};
   struct time_uuid        : uuid<0x2703>{typedef time_uuid type;};
   struct current_uuid     : uuid<0x2704>{typedef current_uuid type;};
   struct temperature_uuid : uuid<0x2705>{typedef temperature_uuid type;};
   struct substance_uuid   : uuid<0x2706>{typedef substance_uuid type;};
   struct intensity_uuid   : uuid<0x2707>{typedef intensity_uuid type;};
   /** @} */
}
#endif // PQS_BASE_UUIDS_HPP_INCLUDED
