#ifndef PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED

#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/base_quantity/uuids.hpp>
#include <pqs/bits/std_ratio.hpp>

namespace pqs{ 

   namespace detail{
      struct base_quantity_exp_base_class{};
   }

   // base quantities are required to be model of meta::identity_function 
   struct base_length : pqs::base_quantity_of<pqs::newtonian_universe::length_uuid>{
      typedef base_length type;
   };

   // base_quantity_exps are required to be models of meta::identity_function
   template <int N, int D>
   struct exp_length : pqs::detail::base_quantity_exp_base_class {
      typedef base_length  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_length type; // identity
   };

}

#endif // PQS_BASE_QUANTITIES_LENGTH_HPP_INCLUDED
