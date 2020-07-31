#ifndef PQS_CONCEPTS_ASSOCIATED_IS_SIMPLE_DIMENSION_LIST_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_IS_SIMPLE_DIMENSION_LIST_HPP_INCLUDED

#include <type_traits>

namespace pqs{ 

   namespace impl {

     /**
      * @brief simple dimension_list default impl
      */
      template <typename D>
      struct is_dimension_list_impl : std::false_type{};

   } //impl

  /**
   * @brief simple dimension_list interface
   */
   template <typename D>
   inline constexpr bool is_dimension_list 
      = impl::is_dimension_list_impl< std::remove_cvref_t<D> >::value;

} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_IS_SIMPLE_DIMENSION_LIST_HPP_INCLUDED
