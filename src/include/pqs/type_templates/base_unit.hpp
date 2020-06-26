#ifndef PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED
#define PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED

#include <pqs/bits/undefined.hpp>

namespace pqs{

    /**
     *  requires explicit specialisation per base unit and quantity system
    */
    template <typename BaseQuantity, typename MeasurementSystem >
    struct base_unit : pqs::undefined{};
}


#endif // PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED
