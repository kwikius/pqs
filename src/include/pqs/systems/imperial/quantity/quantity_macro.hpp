#ifndef PQS_SYSTEMS_IMPERIAL_QUANTITY_MACRO_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_QUANTITY_MACRO_HPP_INCLUDED

#include <cstdint>
#include <pqs/concepts/associated/make_quantity.hpp>

#define PQS_IMPERIAL_QUANTITY_LITERAL(DimName, UnitName) \
 namespace DimName{ \
      template <typename ValueType = double> \
      using UnitName = make_quantity< DimName ## _unit:: UnitName ,ValueType>; \
   } \
    namespace literals{  \
      constexpr auto operator""q_ ## UnitName ## _imperial (unsigned long long v) \
      { \
         return pqs::imperial:: DimName :: UnitName<std::int64_t>{static_cast<std::int64_t>(v)}; \
      } \
      constexpr auto operator""q_ ## UnitName ## _imperial (long double v) \
      { \
         return pqs::imperial:: DimName :: UnitName<pqs::real_type>{static_cast<pqs::real_type>(v)} ; \
      } \
   }

#endif // PQS_SYSTEMS_IMPERIAL_QUANTITY_MACRO_HPP_INCLUDED
