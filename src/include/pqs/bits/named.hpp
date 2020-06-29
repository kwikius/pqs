#ifndef PQS_BITS_NAMED_HPP_INCLUDED
#define PQS_BITS_NAMED_HPP_INCLUDED

#include <pqs/bits/fixed_string.hpp>

namespace pqs{

   template <pqs::basic_fixed_string Name>
   struct named{
       static constexpr auto name = Name;
   };
}

#endif // PQS_BITS_NAMED_HPP_INCLUDED
