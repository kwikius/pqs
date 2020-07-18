#ifndef PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED
#define PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/undefined_arg.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/concepts/base_quantity.hpp>
#include <pqs/concepts/associated/binary_op.hpp>

namespace pqs{

   namespace impl{

     /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/
      /**
       * @brief convenience : derive model of base_quantity 
       * from base_quantity_base_class, for derived to be 
       * models of base_quantity
       */
        struct base_quantity_base_class{};
       /** @} */

      /**
      * @brief convenience : Also derive from base_quantity_of
      * to implement model of base_quantity. 
      * requires Id to be meta_totally ordered
      */
      template <typename Id>
      struct base_quantity_of : pqs::impl::base_quantity_base_class{
         static_assert(pqs::meta::are_totally_ordered<Id,Id>::value, 
         "base_quantity_of requires Id to be totally ordered at compile time");
         using identifier = Id;
         using type = base_quantity_of;
      };


      /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/
      /**
       * @brief make anything derived from base_quantity_base_class a model of base_quantity.
       */
      template <typename T>
         requires std::is_base_of_v<pqs::impl::base_quantity_base_class,T>
      inline constexpr bool is_base_quantity_impl<T> = true;
       /** @} */
      
      /**
      * @addtogroup base_quantity_concept_impl
      * @{ **/
      /**
       /**
       *  @brief fulfill base_quantity requirements for anything derived from base_quantity_base_class, which also needs a member identifier.
       */
      template <typename T>
         requires std::is_base_of_v<pqs::impl::base_quantity_base_class,T>
      struct get_base_quantity_id_impl<T>{
          using type = typename T::identifier;
      };
      /** @} */
   }
}//pqs

#endif // PQS_BITS_BASE_QUANTITY_OF_HPP_INCLUDED
