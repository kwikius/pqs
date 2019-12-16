#ifndef PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
#define PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED

#include <type_traits>

namespace pqs{ namespace meta{

   namespace impl {

    template <typename T, typename Where = false>
     struct identity_function : std::false_type{};

   }
}} //pqs::meta

#endif // PQS_CONCEPTS_META_IDENTITY_FUNCTION_HPP_INCLUDED
