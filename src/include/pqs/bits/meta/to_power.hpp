#ifndef PQS_META_TO_POWER_HPP_INCLUDED
#define PQS_META_TO_POWER_HPP_INCLUDED

namespace pqs{ namespace meta{

   template <intmax_t Val, intmax_t Exp>
   struct to_power{
      typedef to_power type;
      static_assert( ( Val > 0 ) && (Exp > 0 ) ,"unexpected negative values");
      static constexpr intmax_t value = Val * to_power<Val,Exp-1>::value;
   };

   template <intmax_t Val>
   struct to_power<Val,0> {  
      typedef to_power type;
      static constexpr intmax_t value = 1;
   };

}} //pqs::meta

#endif // PQS_META_TO_POWER_HPP_INCLUDED
