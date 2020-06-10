#ifndef PQS_BITS_UNIT_EXP_HPP_INCLUDED
#define PQS_BITS_UNIT_EXP_HPP_INCLUDED

#include <ratio>

namespace pqs{

   template <int N, int D = 1> 
   struct unit_exp : std::ratio<N,D> {};
}

#endif // PQS_BITS_UNIT_EXP_HPP_INCLUDED
