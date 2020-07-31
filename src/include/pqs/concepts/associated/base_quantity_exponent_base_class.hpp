#ifndef PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_BASE_CLASS_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_BASE_CLASS_HPP_INCLUDED

#include <pqs/concepts/base_quantity_exponent.hpp>
#include <pqs/concepts/associated/get_simple_dimension.hpp>

namespace pqs{

   namespace detail{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ 
      * @ brief convenience detect base class 
      */
      struct base_quantity_exp_base_class{}; 
     /** @} */
   }

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
         requires std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T>
      struct get_base_quantity_impl< T > : T::base_type {};
     /** @} */

     /**
      * @todo addtogroup dimension_concept
      */
      template <typename T>
         requires std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T>
      struct get_simple_dimension_impl<T>{
         typedef typename T::simple_dimension type;
      };
   }

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
        template <typename T>
          requires 
            std::is_base_of_v<pqs::detail::base_quantity_exp_base_class,T> &&
            ! base_quantity_exponent<T>
        inline constexpr bool is_custom_base_quantity_exponent_impl<T> = true;
              
     /** @} */
   }//impl

   namespace impl{

     /**
      * @addtogroup base_quantity_exponent_concept_impl
      * @{ **/
      template <typename T>
         requires std::is_base_of_v<
            pqs::detail::base_quantity_exp_base_class,T
         >
      struct get_exponent_impl<T> {
         using type = typename T::exponent;
      };
     /** @} */

   }//impl

}

#endif // PQS_CONCEPTS_ASSOCIATED_BASE_QUANTITY_EXPONENT_BASE_CLASS_HPP_INCLUDED
