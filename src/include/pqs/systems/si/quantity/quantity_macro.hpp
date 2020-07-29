#ifndef PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED
#define PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED

#include <cstdint>
#include <pqs/concepts/associated/make_quantity.hpp>

#define PQS_SI_QUANTITY_LITERAL(DimName, UnitName) \
 namespace DimName{ \
      template <typename ValueType = double> \
      using UnitName = make_quantity< DimName ## _unit:: UnitName ,ValueType>; \
   } \
    namespace literals{  \
      constexpr auto operator""q_ ## UnitName (unsigned long long v) \
      { \
         return pqs::si:: DimName :: UnitName<std::int64_t>{static_cast<std::int64_t>(v)}; \
      } \
      constexpr auto operator""q_ ## UnitName(long double v) \
      { \
         return pqs::si:: DimName :: UnitName<pqs::real_type>{static_cast<pqs::real_type>(v)} ; \
      } \
   }

#endif // PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED
