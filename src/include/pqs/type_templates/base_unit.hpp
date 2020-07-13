#ifndef PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED
#define PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED

#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/concepts/measurement_system.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/value_functions/get_base_unit_symbol.hpp>
#include <pqs/bits/basic_unit.hpp>

namespace pqs{

    template < base_quantity Qb, measurement_system Sm>
    struct base_unit 
    : basic_unit<
         Sm,
         typename make_base_quantity_exp<Qb,std::ratio<1> >::type,
         conversion_factor<std::ratio<1>, exponent10<1> > 
    >{
        template <typename CharSet>
        static constexpr auto name
           = get_base_unit_symbol<Qb,Sm,CharSet>;
    };

}


#endif // PQS_TYPE_TEMPLATES_BASE_UNIT_HPP_INCLUDED
