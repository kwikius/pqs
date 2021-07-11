#ifndef PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED
#define PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED

#include <cstdint>
#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/bits/meta/literal_value.hpp>
#include <type_traits>

#define PQS_SI_QUANTITY_LITERAL(DimName, UnitName) \
    namespace DimName{ \
       template <typename ValueType = double> \
       using UnitName = make_quantity< DimName ## _unit:: UnitName ,ValueType>; \
    } \
    namespace literals{  \
      template <char... V> \
      auto constexpr operator "" q_ ## UnitName() \
      { \
         using value_type = std::remove_cvref_t<decltype(pqs::meta::literal_value<V...>())>; \
         return pqs::si:: DimName :: UnitName<value_type>{pqs::meta::literal_value<V...>()}; \
      } \
   }

#if 0
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
#endif
#endif // PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED
