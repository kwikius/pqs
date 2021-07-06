#ifndef PQS_CONCEPTS_ASSOCIATED_MAKE_QUANTITY_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_MAKE_QUANTITY_HPP_INCLUDED

#include <pqs/bits/config.hpp>
#include <pqs/bits/basic_quantity_fwd.hpp>

namespace pqs{

   namespace impl{
     /**
      * @ brief customisable quantity factory impl
      */
      template <unit Unit, dimensionless_quantity ValueType  >
      struct make_quantity_impl{
         using type = pqs::basic_quantity<Unit,ValueType>;
      };
   }

  /**
   * @ brief quantity factory interface
   */
   template <unit Unit, dimensionless_quantity ValueType = pqs::real_type >
   using make_quantity = 
      typename impl::make_quantity_impl<
         Unit,ValueType
      >::type;

   template <
     auto U , dimensionless_quantity ValueType = pqs::real_type
   >
   requires unit<decltype(U)>
   using make_v_quantity = make_quantity<decltype(U),ValueType>;
   
} // pqs

#endif // PQS_CONCEPTS_ASSOCIATED_MAKE_QUANTITY_HPP_INCLUDED
