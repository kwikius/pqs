#ifndef PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_time : pqs::base_quantity_of<pqs::time_uuid>{
       typedef base_time type;
    };
}

#endif // PQS_BASE_QUANTITIES_TIME_HPP_INCLUDED
