#ifndef DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
#define DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED

#include <pqs/bits/undefined_arg.hpp>

namespace pqs{

   template <typename Qx , typename Qy>
   inline constexpr bool dimensionally_equivalent = undefined_arg<Qx,Qy>{};

}


#endif // DIMENSIONALLY_EQUIVALENT_HPP_INCLUDED
