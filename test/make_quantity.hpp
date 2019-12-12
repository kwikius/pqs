#ifndef PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
#define PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED


#include <tuple>
#include <pqs/meta/type_list.hpp>
#include <pqs/bits/quantity.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/meta/strip_cr.hpp>

namespace pqs{

#if 0
   namespace detail{

      template <int Exp, typename List>
      struct make_unit;

      template <int Exp, typename ... List>
      struct make_unit<Exp, pqs::meta::type_list<List...> > {
         typedef pqs::unit<Exp, List...> type;
      };
   }

   template <int Exp,typename... Tags>
   inline
   constexpr 
   pqs::quantity<
      typename detail::make_unit< 
         Exp,
         typename pqs::meta::pop_back<pqs::meta::type_list<Tags...> >::type 
      >::type,
      typename pqs::meta::back<
         pqs::meta::type_list<Tags...>
      >::type
   > make_quantity(Tags... tags)
   {
      typedef pqs::quantity<
         typename detail::make_unit< 
            Exp,
            typename pqs::meta::pop_back<pqs::meta::type_list<Tags...> >::type 
         >::type,
         typename pqs::meta::back<
            pqs::meta::type_list<Tags...>
         >::type
      > result_type;

      auto tuple = std::make_tuple(tags...);

      return result_type{
         std::get<std::tuple_size<decltype(tuple)>::value- 1
         >(tuple) 
      };
   }
#else

   namespace detail{

      template <int Exp, typename List>
      struct make_unit_impl;


      template <int Exp, typename ... List>
      struct make_unit_impl<Exp, pqs::dimension<List...> > {
         typedef pqs::unit<Exp, List...> type;
      };

      template <int Exp, typename List>
      struct make_unit : make_unit_impl<Exp,typename meta::strip_cr<List>::type>{};
      
   }

   template <int Exp,typename D, typename V>
   inline
   constexpr 
   pqs::quantity<
      typename detail::make_unit< 
         Exp,
         typename meta::eval_if< 
            detail::is_base_dimension_ratio<D>,
            dimension<D>,
            D
         >::type
      >::type,
      V
   > make_quantity(D, V v)
   {
      
      typedef pqs::quantity<
         typename detail::make_unit< 
            Exp,
            typename meta::eval_if< 
               detail::is_base_dimension_ratio<D>,
               dimension<D>,
               D
            >::type
         >::type,
         V
      > result_type;
      return result_type{v};
   }

#endif

}//pqs

#endif // PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
