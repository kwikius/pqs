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
      auto constexpr operator "" _q_ ## UnitName() \
      { \
         using value_type = std::remove_cvref_t<decltype(pqs::meta::literal_value<V...>())>; \
         return pqs::si:: DimName :: UnitName<value_type>{pqs::meta::literal_value<V...>()}; \
      } \
   }

#endif // PQS_SYSTEMS_SI_QUANTITY_MACRO_HPP_INCLUDED
