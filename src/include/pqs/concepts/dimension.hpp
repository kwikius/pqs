#ifndef PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_DIMENSION_HPP_INCLUDED

#include <type_traits>

namespace pqs{

    // no customization
    // intended for dimension<base_dim_exp...> only

/*
       Where T,Lhs,Rhs,are models of dimension
        R is model of ratio
        B is a nodel of meta_bool_constant
        
        binary_op<Lhs,times,Rhs> -> T
        binary_op<Lhs,divides,Rhs> -> T
        binary_op<lhs,to_power,R>  -> T
        unary_op<reciprocal,Lhs> -> T
        binary_op<lhs,equal_to,Rhs> -> B
        binary_op<lhs,not_equal_to,Rhs> -> B
       
*/
   template <typename D>
   struct is_base_quantity_exp_list : std::false_type{};

   template <typename DL, typename DR> 
   struct are_equal_dimensions;

   template <typename DL, typename DR> 
   struct are_not_equal_dimensions;

} //pqs

#endif // PQS_CONCEPTS_DIMENSION_HPP_INCLUDED
