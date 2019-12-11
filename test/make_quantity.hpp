#ifndef PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
#define PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED

namespace pqs{

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

}//pqs

#endif // PQS_TEST_MAKE_QUANTITY_HPP_INCLUDED
