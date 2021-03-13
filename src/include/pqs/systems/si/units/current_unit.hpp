#ifndef PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/current.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs::si::current_unit{

   struct A : si::base_unit<base_current>{};
   struct mA : normative_unit<abstract_current_t, exponent10<-3> >{};
   struct uA : normative_unit<abstract_current_t, exponent10<-6> >{};
   struct nA : normative_unit<abstract_current_t, exponent10<-9> >{};
   struct pA : normative_unit<abstract_current_t, exponent10<-12> >{};
   struct fA : normative_unit<abstract_current_t, exponent10<-15> >{};

} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED
