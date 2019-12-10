
#include <pqs/length.hpp>

using namespace pqs;

struct kilo : std::ratio<3>{};

template <typename... T>
struct unit_;

// dummy for demo only
template <typename ... Tags>
struct find_quantity_value_type{
   typedef float type;
};
// ummy for demo only
template <typename... Tags>
int make_quantity(typename find_quantity_value_type<Tags...>::type V)
{
  return 1;
}

struct affine;

void quantity_syntax_test1() 
{
   // anonymous or r-value quantity
   auto qa = quantity<
      unit<
         dimension<
            dim_length<1>, 
            dim_time<-1>,
            dim_mass<2>, 
            dim_temperature<3>
         >, 3  //<-- exponent
      >,double
   > {};

   // named quantity
   auto qb = quantity<length_unit::mm, double>{};
   // alternative syntax
   auto qc = length::mm<>{};
  // non si unit
   auto qd = length::ft<>{};
   // same type
   qb = qc;

   // or create from a bag of tags ...
   auto qe = make_quantity<
      affine,  // make an affine quantity
      kilo,    // exponenet
      dim_length<1>,
      double,  // value_type
      dim_time<-1>,
      dim_mass<2>,
      dim_temperature<3>
   >(20);

}