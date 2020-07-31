#ifndef PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_HPP_INCLUDED

#include <type_traits>
//#include <pqs/concepts/associated/is_custom_dimension_list.hpp>
//#include <pqs/concepts/associated/is_custom_base_quantity_exponent.hpp>

namespace pqs{

   namespace impl {

     /**
      * @brief custom dimension impl
      */
//      template <typename D>
//      inline constexpr bool is_custom_dimension_impl  =
//         is_custom_dimension_list<D> || 
//         is_custom_base_quantity_exponent<D>
//      ;

      template <typename D>
      inline constexpr bool is_custom_dimension_impl = false;
   }

  /**
   * @brief custom dimension interface
   */
   template <typename D>
   inline constexpr bool is_custom_dimension =
      impl::is_custom_dimension_impl<typename std::remove_cvref_t<D> >;

} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_IS_CUSTOM_DIMENSION_HPP_INCLUDED
