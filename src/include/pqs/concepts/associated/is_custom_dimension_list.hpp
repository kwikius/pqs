#ifndef PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_LIST_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_LIST_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   namespace impl{
  
     /**
      * @brief is_custom_dimension_list impl - default
      */
      template <typename T>
      inline constexpr bool is_custom_dimension_list_impl = false;

   }

  /**
   * @brief is_custom dimension_list - interface
   */
   template<typename T>
   inline constexpr bool is_custom_dimension_list =
      impl::is_custom_dimension_list_impl<std::remove_cvref_t<T> >;

}// pqs


#endif // PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_LIST_HPP_INCLUDED
