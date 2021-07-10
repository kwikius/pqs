#ifndef PQS_META_IS_DIGIT_HPP_INCLUDED
#define PQS_META_IS_DIGIT_HPP_INCLUDED

namespace pqs{ namespace meta{

   template <char C> constexpr bool is_digit = (C >= '0') && ( C <= '9');

}} //pqs::meta

#endif // PQS_META_IS_DIGIT_HPP_INCLUDED
