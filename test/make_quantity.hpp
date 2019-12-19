#ifndef PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
#define PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED


#include <tuple>
#include <pqs/meta/type_list.hpp>
#include <pqs/bits/quantity.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/meta/strip_cr.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/undefined_arg.hpp>

namespace pqs{


      template <int Exp,typename D>
      struct make_unit : pqs::meta::eval_if<
            pqs::is_base_quantity_exp<D>,
               base_unit<D,Exp>,
            pqs::is_dimension<D>,
               pqs::derived_unit<D,Exp>,
            pqs::is_derived_dimension<D>,
               pqs::named_unit<D,Exp>,
            pqs::undefined_arg<D>
         >{ };


   template <int Exp,typename D, typename V>
   inline
   constexpr 
   pqs::quantity<typename make_unit<Exp,D>::type,V>
   make_quantity(D, V v)
   {
      typedef pqs::quantity<
         typename make_unit<Exp,D>::type,
         V
      > result_type;
      return result_type{v};
   }

}//pqs

#endif // PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
