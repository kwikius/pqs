#ifndef PQS_INSTANCE_BASIC_QUANTITY_FWD_HPP_INCLUDED
#define PQS_INSTANCE_BASIC_QUANTITY_FWD_HPP_INCLUDED

#include <pqs/concepts/unit.hpp>
#include <pqs/concepts/dimensionless_quantity.hpp>

namespace pqs{

   template <unit Unit, dimensionless_quantity ValueType>
   struct basic_quantity;

}

#endif // PQS_INSTANCE_BASIC_QUANTITY_FWD_HPP_INCLUDED
