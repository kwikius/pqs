#ifndef PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED

#include <pqs/bits/undefined_arg.hpp>

namespace pqs{

   /**
    *  @brief true if Qx , Qy are dimensionally equivalent
    *  (Invoking the default will cause compile fail)
    */
   template <typename Qx , typename Qy>
   inline constexpr bool dimensionally_equivalent = false;//undefined_arg<Qx,Qy>{};

}

#endif // PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
