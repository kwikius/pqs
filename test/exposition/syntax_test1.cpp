
#include <pqs/exposition/length.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/meta/type_list.hpp>
#include <tuple>

using namespace pqs;
using namespace pqs_exposition;

struct kilo : std::ratio<3>{};

template <typename... T>
struct unit_;

// dummy for demo only
template <typename ... Tags>
struct find_quantity_value_type{
   typedef float type;
};

void quantity_syntax_test1() 
{

   auto qx = quantity<
      unit<
         3,          
         pqs_exposition::exp<base_length,1>, 
         pqs_exposition::exp<base_time,-1>,
         pqs_exposition::exp<base_mass,2>, 
         pqs_exposition::exp<base_temperature,3>
      >,
      double
   >{};
   
   // anonymous or r-value quantity
   auto qa = quantity<
      derived_unit<
         dimension<
            pqs_exposition::exp<base_length,1>, 
            pqs_exposition::exp<base_time,-1>,
            pqs_exposition::exp<base_mass,2>, 
            pqs_exposition::exp<base_temperature,3>
         >, 3  //<-- exponent
      >,double
   > {};

   // named quantity
   auto qb = quantity<length_unit::mm, double>{};
   // alternative syntax
   auto qc = length::mm<>{};
  // non si unit
   auto qd = length::ft<>{};

  // suppress set not used warnings
  (void) qx;
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;

   // same type
  // qb = qx;

}