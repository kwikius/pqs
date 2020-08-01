#ifndef PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED

namespace pqs{

   /**
    *  @brief true if Qx , Qy are dimensionally equivalent
    */
   template <typename Qx , typename Qy>
   inline constexpr bool dimensionally_equivalent = false;

}

#endif // PQS_CONCEPTS_ASSOCIATED_DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
