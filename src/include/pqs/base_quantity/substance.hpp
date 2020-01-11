#ifndef PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_substance : pqs::base_quantity_of<pqs::newtonian_universe::substance_uuid>{
       typedef base_substance type;
    };
}

#endif //PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
