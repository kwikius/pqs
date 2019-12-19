#ifndef PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_temperature : pqs::base_quantity_of<pqs::temperature_uuid>{
       typedef base_temperature type;
    };
}

#endif //PQS_BASE_QUANTITIES_TEMPERATURE_HPP_INCLUDED
