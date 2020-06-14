#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/concepts/base_quantity_exp_list.hpp>

namespace pqs{

   template <typename D>
   struct is_derived_dimension : pqs::meta::or_<
      is_derived_from_base_quantity_exp_list<D>,
      is_derived_from_base_quantity_exp<D>
   >{};

   template <typename T>
   struct is_dimension : pqs::meta::or_<
      pqs::is_base_quantity_exp<T>,
      pqs::is_base_quantity_exp_list<T>,
      pqs::is_derived_dimension<T>
   >{};

}

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
