#ifndef PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>

namespace pqs{ 

    struct base_mass : pqs::base_quantity_of<pqs::mass_uuid>{
       typedef base_mass type;
    };
}

#endif // PQS_BASE_QUANTITIES_MASS_HPP_INCLUDED
