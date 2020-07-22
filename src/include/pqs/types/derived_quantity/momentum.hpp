#ifndef PQS_DERIVED_QUANTITY_MOMENTUM_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_MOMENTUM_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/derived_quantity/speed.hpp>

namespace pqs{
  
   constexpr inline auto abstract_momentum_v = abstract_mass<> * abstract_speed_v;
   using abstract_momentum_t = std::remove_cvref_t<decltype(abstract_momentum_v)>;
}

#endif // PQS_DERIVED_QUANTITY_MOMENTUM_UNIT_HPP_INCLUDED
