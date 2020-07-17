#ifndef PQS_BITS_NAMED_HPP_INCLUDED
#define PQS_BITS_NAMED_HPP_INCLUDED

#include <pqs/types/fixed_string.hpp>

namespace pqs{

   template <pqs::basic_fixed_string Name>
   struct named{

       template <typename CharSet>
       static constexpr pqs::basic_fixed_string name = Name;
   };
}

#endif // PQS_BITS_NAMED_HPP_INCLUDED
