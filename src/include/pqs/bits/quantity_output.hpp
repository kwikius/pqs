#ifndef PQS_BITS_QUANTITY_OUTPUT_HPP_INCLUDED
#define PQS_BITS_QUANTITY_OUTPUT_HPP_INCLUDED

#include <iostream>
#include <pqs/concepts/associated/quantity_to_fixed_string.hpp>

namespace pqs{

   template <typename CharSet, quantity Q>
   std::ostream & output(std::ostream & out, Q const & q)
   {
      return out << get_numeric_value(q)
         << " " <<  unit_to_fixed_string<CharSet>(q) ;
   }
}

#endif // PQS_BITS_QUANTITY_OUTPUT_HPP_INCLUDED
