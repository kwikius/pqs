#ifndef PQS_SI_UNITS_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/moment_of_inertia.hpp>

namespace pqs{ namespace si { namespace moment_of_inertia_unit{

   struct kg_s2 : pqs::si::normative_unit<
      abstract_moment_of_inertia_t
   >{};

}}} // pqs::si::moment_of_inertia_unit

#endif // PQS_SI_UNITS_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED
