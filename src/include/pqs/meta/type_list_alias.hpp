#ifndef PQS_META_TYPE_LIST_ALIAS_HPP_INCLUDED
#define PQS_META_TYPE_LIST_ALIAS_HPP_INCLUDED


namespace pqs{ namespace meta{

      template <typename ListFrom>
      struct type_list_alias;

      template < template <typename...> class ListFrom, typename... Elems >
      struct type_list_alias< ListFrom<Elems...> > {
         template <template <typename...> class ListTo >
         struct apply {
            typedef ListTo<Elems...> type;
         };
      };

}} // pqs::meta

#endif // PQS_META_TYPE_LIST_ALIAS_HPP_INCLUDED
