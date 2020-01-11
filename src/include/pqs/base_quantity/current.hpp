#ifndef PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_current : pqs::base_quantity_of<pqs::newtonian_universe::current_uuid>{
       typedef base_current type;
    };
}

#endif //PQS_BASE_QUANTITIES_CURRENT_HPP_INCLUDED
