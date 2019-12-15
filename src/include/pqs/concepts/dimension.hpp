#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

    // no customization
    // intended for dimension<base_dim_exp...> only
   template <typename D>
   struct is_dimension : std::false_type{};

   template <typename LhsD, typename RhsD>
   struct add_dimensions;

   template <typename LhsD, typename RhsD>
   struct subtract_dimensions;

   template <typename LhsD, typename Ratio>
   struct multiply_dimension;

   template <typename LhsD, typename Ratio>
   struct divide_dimension;

   template <typename D>
   struct negate_dimension;

   template <typename DL, typename DR> 
   struct are_equal_dimensions;

   template <typename DL, typename DR> 
   struct are_not_equal_dimensions;

} //pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
