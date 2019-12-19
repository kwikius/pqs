#ifndef PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_intensity : pqs::base_quantity_of<pqs::intensity_uuid>{
       typedef base_intensity type;
    };
}

#endif //PQS_BASE_QUANTITIES_INTENSITY_HPP_INCLUDED
