#ifndef PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED

#include <type_traits>

#include <pqs/bits/where.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace pqs{

/*
  Interesting on base_quantity v base_dimension
  http://www.science-campus.com/physics/measurement/meas_2_6.html
*/

/*
   model of base quantity requires
    meta::totally_ordered
    meta::identity_function

*/

   template <typename T>
   struct is_base_quantity;

   namespace impl{

      template <typename T, typename Where = void>
      struct is_base_quantity_impl : std::false_type{};
      
      // get_uuid. 
      template <typename BaseQuantity, typename Where = void>
      struct get_base_quantity_id_impl : pqs::undefined{};
      
   }

   template <typename T>
   struct is_base_quantity : impl::is_base_quantity_impl<T>{};

   template <typename BaseQuantity, typename Where = void>
   struct get_base_quantity_id : impl::get_base_quantity_id_impl<BaseQuantity>{};

}

#endif // PQS_CONCEPTS_BASE_QUANTITY_HPP_INCLUDED
